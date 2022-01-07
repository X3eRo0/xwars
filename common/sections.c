//
// Created by X3eRo0 on 2/28/2021.
//
// modified @brightprogrammer on 10/7/2021
//     modification : in function "find_section_entry_by_name" changed parameter type "char*" to "const char*"
//                    same thing done in "set_section entry" function and many more functions
//                    CHECK "diff" to see changes. Build Tested! Works!
//     reason : ISO C++11 forbids using char* as string

#include "const.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "bitmap.h"
#include "sections.h"

section_entry* init_section_entry()
{
    // initialize section

    section_entry* sec_entry = (section_entry*)malloc(sizeof(section_entry));
    sec_entry->m_name = NULL;
    sec_entry->v_size = 0;
    sec_entry->v_addr = 0;
    sec_entry->a_size = 0;
    sec_entry->m_flag = PERM_READ;
    sec_entry->m_buff = NULL;
    sec_entry->m_ofst = 0;
    sec_entry->next = NULL;

    return sec_entry;
}

u32* get_reference(section* sec, u32 addr, u8 opt_perm)
{
    // read byte
    section_entry* sec_entry = find_section_entry_by_addr(sec, addr);
    if (sec_entry != NULL) {
        if (!(sec_entry->m_flag & PERM_READ) || !(sec_entry->m_flag & (opt_perm & 7))) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
            // segfault(XSIGSEGV, sec_entry, addr);
        }
        if (addr + 3 >= sec_entry->v_addr + sec_entry->v_size) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
        }
        if (((addr >> 12) & 0xffff) == 0x1337) {
            u8 oprn = 0;
            if (opt_perm & DONT_DISR) {
                return ((u32*)&sec_entry->m_buff[addr - sec_entry->v_addr]);
            }
            if (opt_perm == PERM_EXEC) {
                oprn = make_oprn(get_current_bitmap_bot(), oprn_cx);
            } else if (opt_perm == PERM_READ) {
                oprn = make_oprn(get_current_bitmap_bot(), oprn_r);
            } else if (opt_perm == PERM_WRITE) {
                oprn = make_oprn(get_current_bitmap_bot(), oprn_w);
            }
            if (addr - sec_entry->v_addr < XWARS_MEM_SIZE) {
                set_oprn_at_idx(addr - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 1 - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 2 - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 3 - sec_entry->v_addr, oprn);
            }
        }
        return ((u32*)&sec_entry->m_buff[addr - sec_entry->v_addr]);
    }

    raise_signal(sec->errors, XSIGSEGV, addr, 0);
    // segfault(XSIGSEGV, sec_entry, addr);
    return NULL;
}

u8 read_byte(section* sec, u32 addr, u8 opt_perm)
{
    // read byte
    section_entry* sec_entry = find_section_entry_by_addr(sec, addr);
    if (sec_entry != NULL) {
        if (!(sec_entry->m_flag & PERM_READ) || !(sec_entry->m_flag & opt_perm)) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
            // segfault(XSIGSEGV, sec_entry, addr);
        }
        if (addr >= sec_entry->v_addr + sec_entry->v_size) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
        }
        if (((addr >> 12) & 0xffff) == 0x1337) {
            u8 oprn = 0;
            if (opt_perm == PERM_EXEC) {
                oprn = make_oprn(get_current_bitmap_bot(), oprn_cx);
            } else {
                oprn = make_oprn(get_current_bitmap_bot(), oprn_r);
            }

            if (addr - sec_entry->v_addr < XWARS_MEM_SIZE) {
                set_oprn_at_idx(addr - sec_entry->v_addr, oprn);
            }
        }
        return (u8) * ((u8*)&sec_entry->m_buff[addr - sec_entry->v_addr]);
    }
    raise_signal(sec->errors, XSIGSEGV, addr, 0);
    // segfault(XSIGSEGV, sec_entry, addr);
    return (u8)E_ERR;
}

u16 read_word(section* sec, u32 addr, u8 opt_perm)
{
    // read word
    section_entry* sec_entry = find_section_entry_by_addr(sec, addr);
    if (sec_entry != NULL) {
        if (!(sec_entry->m_flag & PERM_READ) || !(sec_entry->m_flag & opt_perm)) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
            // segfault(XSIGSEGV, sec_entry, addr);
        }
        if (addr + 1 >= sec_entry->v_addr + sec_entry->v_size) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
        }
        if (((addr >> 12) & 0xffff) == 0x1337) {
            u8 oprn = 0;
            if (opt_perm == PERM_EXEC) {
                oprn = make_oprn(get_current_bitmap_bot(), oprn_cx);
            } else {
                oprn = make_oprn(get_current_bitmap_bot(), oprn_r);
            }

            if (addr - sec_entry->v_addr < XWARS_MEM_SIZE) {
                set_oprn_at_idx(addr - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 1 - sec_entry->v_addr, oprn);
            }
        }
        return (u16) * ((u16*)&sec_entry->m_buff[addr - sec_entry->v_addr]);
    }

    raise_signal(sec->errors, XSIGSEGV, addr, 0);
    // segfault(XSIGSEGV, sec_entry, addr);
    return (u16)E_ERR;
}

u32 read_dword(section* sec, u32 addr, u8 opt_perm)
{
    // read dword
    section_entry* sec_entry = find_section_entry_by_addr(sec, addr);
    if (sec_entry != NULL) {
        if (!(sec_entry->m_flag & PERM_READ) || !(sec_entry->m_flag & opt_perm)) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
            // segfault(XSIGSEGV, sec_entry, addr);
        }
        if (addr + 3 >= sec_entry->v_addr + sec_entry->v_size) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
        }
        if (((addr >> 12) & 0xffff) == 0x1337) {
            u8 oprn = 0;
            if (opt_perm == PERM_EXEC) {
                oprn = make_oprn(get_current_bitmap_bot(), oprn_cx);
            } else {
                oprn = make_oprn(get_current_bitmap_bot(), oprn_r);
            }
            if (addr - sec_entry->v_addr < XWARS_MEM_SIZE) {
                set_oprn_at_idx(addr - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 1 - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 2 - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 3 - sec_entry->v_addr, oprn);
            }
        }
        return (u32) * ((u32*)&sec_entry->m_buff[addr - sec_entry->v_addr]);
    }

    raise_signal(sec->errors, XSIGSEGV, addr, 0);
    // segfault(XSIGSEGV, sec_entry, addr);
    return (u32)E_ERR;
}

u32 write_section_entry_to_file(section_entry* sec_entry, FILE* file)
{

    fwrite("\xEF\xBE\xAD\xDE", sizeof(u32), 1, file);
    fwrite(sec_entry->m_name, sizeof(u8), strlen(sec_entry->m_name) + 1, file);
    fwrite(&sec_entry->v_size, sizeof(u32), 1, file);
    fwrite(&sec_entry->v_addr, sizeof(u32), 1, file);
    fwrite(&sec_entry->m_flag, sizeof(u32), 1, file);
    fwrite(&sec_entry->m_ofst, sizeof(u32), 1, file);
    fwrite(sec_entry->m_buff, sizeof(u8), sec_entry->m_ofst, file);

    return E_OK;
}

u32 write_raw_section_entry_to_file(section_entry* sec_entry, FILE* file)
{
    fwrite(sec_entry->m_buff, sizeof(u8), sec_entry->m_ofst, file);
    return E_OK;
}

u32 append_byte(section* sec, section_entry* sec_entry, u8 byte)
{
    // write byte
    if (sec_entry->m_ofst >= sec_entry->v_size) {
        raise_signal(sec->errors, XSIGSEGV, sec_entry->v_addr + sec_entry->m_ofst, 0);
        // segfault(XSIGSEGV, sec_entry, sec_entry->v_addr + sec_entry->m_ofst);
    }
    *((u8*)&sec_entry->m_buff[sec_entry->m_ofst]) = byte;
    sec_entry->m_ofst += sizeof(u8);
    return sizeof(u8);
}

u32 append_word(section* sec, section_entry* sec_entry, u16 word)
{
    // write word
    if (sec_entry->m_ofst + 1 >= sec_entry->v_size) {
        raise_signal(sec->errors, XSIGSEGV, sec_entry->v_addr + sec_entry->m_ofst, 0);
        // segfault(XSIGSEGV, sec_entry, sec_entry->v_addr + sec_entry->m_ofst);
    }
    *((u16*)&sec_entry->m_buff[sec_entry->m_ofst]) = word;
    sec_entry->m_ofst += sizeof(u16);
    return sizeof(u16);
}

u32 append_dword(section* sec, section_entry* sec_entry, u32 dword)
{
    // write dword
    if (sec_entry->m_ofst + 3 >= sec_entry->v_size) {
        raise_signal(sec->errors, XSIGSEGV, sec_entry->v_addr + sec_entry->m_ofst, 0);
        // segfault(XSIGSEGV, sec_entry, sec_entry->v_addr + sec_entry->m_ofst);
    }

    *((u32*)&sec_entry->m_buff[sec_entry->m_ofst]) = dword;
    sec_entry->m_ofst += sizeof(u32);
    return sizeof(u32);
}

u32 memcpy_to_buffer(section* sec, section_entry* sec_entry, const char* buffer, u32 size)
{

    u32 b_written = 0;
    for (u32 i = 0; i < size; i++) {
        b_written += append_byte(sec, sec_entry, buffer[i]);
    }

    return b_written;
}

u32 memcpy_from_buffer(section* sec, char* buffer, section_entry* sec_entry, u32 size)
{

    u32 b_written = 0;
    for (u32 i = 0; i < size; i++) {
        buffer[i] = (char)read_byte(sec, sec_entry->v_addr, PERM_READ);
        b_written++;
    }

    return b_written;
}

u32 write_byte(section* sec, u32 addr, u8 byte)
{
    // write byte
    section_entry* sec_entry = find_section_entry_by_addr(sec, addr);
    if (sec_entry != NULL) {
        if (!(sec_entry->m_flag & (PERM_WRITE))) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
            // segfault(XSIGSEGV, sec_entry, addr);
        }
        if (addr >= sec_entry->v_addr + sec_entry->v_size) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
        }
        if (((addr >> 12) & 0xffff) == 0x1337) {
            u8 oprn = make_oprn(get_current_bitmap_bot(), oprn_w);
            if (addr - sec_entry->v_addr < XWARS_MEM_SIZE) {
                set_oprn_at_idx(addr - sec_entry->v_addr, oprn);
            }
        }
        *((u8*)&sec_entry->m_buff[addr - sec_entry->v_addr]) = byte;
        return sizeof(u8);
    }

    raise_signal(sec->errors, XSIGSEGV, addr, 0);
    // segfault(XSIGSEGV, sec_entry, addr);
    return E_ERR;
}

u32 write_word(section* sec, u32 addr, u16 word)
{
    // write word
    section_entry* sec_entry = find_section_entry_by_addr(sec, addr);
    if (sec_entry != NULL) {
        if (!(sec_entry->m_flag & (PERM_WRITE))) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
            // segfault(XSIGSEGV, sec_entry, addr);
        }
        if (addr + 1 >= sec_entry->v_addr + sec_entry->v_size) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
        }
        if (((addr >> 12) & 0xffff) == 0x1337) {
            u8 oprn = make_oprn(get_current_bitmap_bot(), oprn_w);
            if (addr - sec_entry->v_addr < XWARS_MEM_SIZE) {
                set_oprn_at_idx(addr - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 1 - sec_entry->v_addr, oprn);
            }
        }
        *((u16*)&sec_entry->m_buff[addr - sec_entry->v_addr]) = word;
        return sizeof(u16);
    }

    raise_signal(sec->errors, XSIGSEGV, addr, 0);
    // segfault(XSIGSEGV, sec_entry, addr);
    return E_ERR;
}

u32 write_dword(section* sec, u32 addr, u32 dword)
{
    // write dword
    section_entry* sec_entry = find_section_entry_by_addr(sec, addr);
    if (sec_entry != NULL) {
        if (!(sec_entry->m_flag & PERM_WRITE)) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
            // segfault(XSIGSEGV, sec_entry, addr);
        }
        if (addr + 3 >= sec_entry->v_addr + sec_entry->v_size) {
            raise_signal(sec->errors, XSIGSEGV, addr, 0);
        }
        if (((addr >> 12) & 0xffff) == 0x1337) {
            u8 oprn = make_oprn(get_current_bitmap_bot(), oprn_w);
            if (addr - sec_entry->v_addr < XWARS_MEM_SIZE) {
                set_oprn_at_idx(addr - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 1 - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 2 - sec_entry->v_addr, oprn);
                set_oprn_at_idx(addr + 3 - sec_entry->v_addr, oprn);
            }
        }

        *((u32*)&sec_entry->m_buff[addr - sec_entry->v_addr]) = dword;
        return sizeof(u32);
    }
    raise_signal(sec->errors, XSIGSEGV, addr, 0);
    // segfault(XSIGSEGV, sec_entry, addr);
    return E_ERR;
}

u32 set_section_entry(section_entry* sec_entry, const char* name, u32 size, u32 addr, u32 flag)
{
    // set section entry members

    if ((size % 0x1000) != 0) {
        size = ((size / 0x1000) + 1) * 0x1000;
    }

    // FIXME: check if any other section entry already has the same values

    // if size is greater than the limit, adjust the size
    size = size > MAX_ALLOC_SIZE ? MAX_ALLOC_SIZE : size;

    if (name != NULL) {
        if (sec_entry->m_name == NULL) {
            sec_entry->m_name = strdup(name);
        } else {
            sec_entry->m_name = realloc(sec_entry->m_name, MAX_NAME_SIZE);
            strncpy(sec_entry->m_name, name, MAX_NAME_SIZE);
        }
    }

    sec_entry->v_size = size;
    sec_entry->v_addr = addr;
    sec_entry->m_flag = flag;
    sec_entry->m_ofst = 0;
    sec_entry->a_size = 0;
    sec_entry->m_buff = (char*)realloc(sec_entry->m_buff, size);
    memset(sec_entry->m_buff, 0, size);
    sec_entry->next = NULL;

    return E_OK;
}

u32 show_section_entry_info(section_entry* sec_entry)
{

    printf(KGRN "%8s" KNRM, sec_entry->m_name);
    printf(KBLU "        #0x%X" KNRM, sec_entry->v_size);
    printf(KYEL "    ");
    if (sec_entry->m_flag & PERM_READ) {
        printf("r");
    } else {
        printf("-");
    }

    if (sec_entry->m_flag & PERM_WRITE) {
        printf("w");
    } else {
        printf("-");
    }

    if (sec_entry->m_flag & PERM_EXEC) {
        printf("x");
    } else {
        printf("-");
    }
    printf(KNRM "       ");

    printf(KRED "#0x%06X" KNRM, sec_entry->m_ofst);

    printf(KNRM "       ");

    printf(KGRN "#0x%06X\n" KNRM, sec_entry->v_addr);

    return E_OK;
}

u32 fini_section_entry(section_entry* sec_entry)
{
    // destroy section structure

    if (sec_entry->m_buff) {
        free(sec_entry->m_buff);
        sec_entry->m_buff = NULL;
    }

    if (sec_entry->m_name) {
        free(sec_entry->m_name);
        sec_entry->m_name = NULL;
    }

    sec_entry->v_size = 0;
    sec_entry->v_addr = 0;
    sec_entry->a_size = 0;
    sec_entry->m_ofst = 0;
    sec_entry->m_flag = 0;

    sec_entry->next = NULL;
    free(sec_entry);
    sec_entry = NULL;

    return E_OK;
}

section* init_section()
{
    // initialize section list

    section* sec = (section*)calloc(1, sizeof(section));
    sec->sections = NULL;
    sec->n_sections = 0;
    sec->errors = (signal_report*)calloc(1, sizeof(signal_report));
    return sec;
}

section_entry* add_section(section* sec, const char* name, u32 size, u32 addr, u32 flag)
{
    // add new section to section list

    size = (size % 0x1000) == 0 ? size : (size / 0x1000 + 1) * 0x1000;
    size = size > MAX_ALLOC_SIZE ? MAX_ALLOC_SIZE : size;
    size = size == 0 ? 0x1000 : size;

    if ((u64)addr + (u64)size > 0x100000000) {
        return NULL;
    }

    if (sec == NULL) {
        return NULL;
    }

    if (sec->sections == NULL) {
        sec->sections = init_section_entry();
        sec->n_sections++;
        set_section_entry(sec->sections, name, size, addr, flag);
        return sec->sections;
    }

    section_entry* temp = sec->sections;
    section_entry* prev = NULL;

    // if new section's v_addr is smaller than the head of the list then change
    // the head of the list

    if (addr + size < temp->v_addr) {

        // this check ensures that the first section in the list is always
        // at the lowest address possible

        section_entry* new = init_section_entry();
        sec->n_sections++;
        set_section_entry(new, name, size, addr, flag);
        new->next = sec->sections;
        sec->sections = new;
        return new;
    }

    while (temp != NULL) {

        if (addr >= temp->v_addr && addr < section_end(temp)) {
            if (temp->v_size != size && temp->next != NULL && temp->v_addr + size < temp->next->v_addr) {
                temp->v_size = size;
                temp->m_buff = realloc(temp->m_buff, size);
                memset(temp->m_buff, 0, size);
            }
            if (temp->m_flag != flag) {
                temp->m_flag = flag;
            }

            return temp;
        }

        if (prev != NULL) {
            if ((section_end(prev) < addr) && (addr + size < temp->v_addr)) {
                // insert the new section here
                break;
            }
        }

        prev = temp;
        temp = temp->next;
    }

    prev->next = init_section_entry();
    sec->n_sections++;
    set_section_entry(prev->next, name, size, addr, flag);
    prev->next->next = temp;

    return prev->next;
}

u32 remove_section_by_name(section* section, const char* name)
{
    section_entry* temp = find_section_entry_by_name(section, name);
    section_entry* prev = NULL;
    section_entry* text = find_section_entry_by_name(section, ".text");
    section_entry* data = find_section_entry_by_name(section, ".data");
    section_entry* stack = find_section_entry_by_name(section, "stack");

    temp = section->sections;

    // if required section is the first section

    if (strncmp(section->sections->m_name, name, strlen(temp->m_name)) == 0) {
        section->sections = section->sections->next;
        fini_section_entry(temp);
        temp = NULL;
        return E_OK;
    }

    while (temp != NULL) {
        if (strncmp(temp->m_name, name, strlen(temp->m_name)) == 0) {
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    // if temp is NULL we are deallocating a section which does not exist
    if (temp == NULL) {
        return E_ERR;
    }

    if (prev != NULL) {
        prev->next = temp->next;
    }

    fini_section_entry(temp);
    temp = NULL;
    prev = NULL;
    return E_OK;
}

u32 remove_section_by_addr(section* section, u32 addr)
{
    section_entry* temp = find_section_entry_by_addr(section, addr);
    section_entry* prev = NULL;
    section_entry* text = find_section_entry_by_name(section, ".text");
    section_entry* data = find_section_entry_by_name(section, ".data");
    section_entry* stack = find_section_entry_by_name(section, "stack");

    temp = section->sections;
    while (temp != NULL) {
        if (temp->v_addr == addr) {
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    // if temp is NULL we are deallocating a section which does not exist
    if (temp == NULL) {
        return E_ERR;
    }

    if (prev != NULL) {
        prev->next = temp->next;
    }
    section->n_sections--;
    fini_section_entry(temp);
    temp = NULL;
    prev = NULL;
    return E_OK;
}

section_entry* find_section_entry_by_name(section* sec, const char* name)
{

    section_entry* temp = sec->sections;
    while (temp != NULL) {
        if (temp->m_name != NULL && !strncmp(temp->m_name, name, strlen(name))) {
            return temp;
        }
        temp = temp->next;
    }

    raise_signal(sec->errors, XSIGSEGV, 0, 0);
    // segfault(XSIGSEGV, NULL, 0);
    return NULL;
}

section_entry* find_section_entry_by_addr(section* sec, u32 addr)
{

    section_entry* temp = sec->sections;
    while (temp != NULL) {
        if (addr >= temp->v_addr && addr < temp->v_addr + temp->v_size) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

u32 show_section_info(section* sec)
{

    // FIXME : COMMENT FOR RELEASE
    printf("[" KGRN "+" KNRM "] Dumping Section Info\n");
    printf("Section Name      Size    Flags    Size on Disk      v-address\n");

    section_entry* temp = sec->sections;
    while (temp != NULL) {
        show_section_entry_info(temp);
        temp = temp->next;
    }
    return E_OK;
}

u32 write_section_to_file(section* sec, FILE* file)
{

    section_entry* temp = sec->sections;
    while (temp != NULL) {
        write_section_entry_to_file(temp, file);
        temp = temp->next;
    }

    return E_OK;
}

u32 write_raw_section_to_file(section* sec, FILE* file)
{
    section_entry* temp = sec->sections;
    while (temp != NULL) {
        write_raw_section_entry_to_file(temp, file);
        temp = temp->next;
    }

    return E_OK;
}

u32 write_buffer_to_section_by_name(section* sec, const char* name, u32 buffer, u32 write_as_flag)
{

    if (sec == NULL) {
        return E_ERR;
    }

    if (sec->sections == NULL) {
        return E_ERR;
    }

    section_entry* temp = sec->sections;

    while (temp != NULL) {
        if (!strncmp(temp->m_name, name, strlen(name))) {
            break;
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        return E_ERR;
    }

    switch (write_as_flag) {
    case WRITE_AS_BYTE:
        append_byte(sec, temp, (u8)buffer);
        return E_OK;
    case WRITE_AS_WORD:
        append_word(sec, temp, (u16)buffer);
        return E_OK;
    case WRITE_AS_DWORD:
        append_dword(sec, temp, (u32)buffer);
        return E_OK;
    default:
        return E_ERR;
    }
}

u32 write_buffer_to_section_by_addr(section* sec, u32 addr, u32 buffer, u32 write_as_flag)
{

    if (sec == NULL) {
        return E_ERR;
    }

    if (sec->sections == NULL) {
        return E_ERR;
    }

    section_entry* temp = find_section_entry_by_addr(sec, addr);

    if (temp == NULL) {
        return E_ERR;
    }

    switch (write_as_flag) {
    case WRITE_AS_BYTE:
        append_byte(sec, temp, (u8)buffer);
        return E_OK;
    case WRITE_AS_WORD:
        append_word(sec, temp, (u16)buffer);
        return E_OK;
    case WRITE_AS_DWORD:
        append_dword(sec, temp, (u32)buffer);
        return E_OK;
    default:
        return E_ERR;
    }
}

u32 memcpy_buffer_to_section_by_name(section* sec, const char* name, const char* buffer, u32 size)
{

    if (sec == NULL) {
        return E_ERR;
    }

    if (sec->sections == NULL) {
        return E_ERR;
    }

    section_entry* temp = sec->sections;
    while (temp != NULL) {
        if (!strncmp(temp->m_name, name, strlen(name))) {
            break;
        }
        temp = temp->next;
    }
    return memcpy_to_buffer(NULL, temp, buffer, size);
}

u32 memcpy_buffer_to_section_by_addr(section* sec, u32 addr, const char* buffer, u32 size)
{

    if (sec == NULL) {
        return E_ERR;
    }

    if (sec->sections == NULL) {
        return E_ERR;
    }

    section_entry* temp = sec->sections;
    while (temp != NULL) {
        if (addr >= temp->v_addr && addr < temp->v_addr + temp->v_size) {
            break;
        }
        temp = temp->next;
    }
    return memcpy_to_buffer(NULL, temp, buffer, size);
}

u32 memcpy_buffer_from_section_by_name(section* sec, char* buffer, const char* name, u32 size)
{

    if (sec == NULL) {
        return E_ERR;
    }

    if (sec->sections == NULL) {
        return E_ERR;
    }

    section_entry* temp = sec->sections;
    while (temp != NULL) {
        if (!strncmp(temp->m_name, name, strlen(name))) {
            break;
        }
        temp = temp->next;
    }
    return memcpy_from_buffer(NULL, buffer, temp, size);
}

u32 memcpy_buffer_from_section_by_addr(section* sec, char* buffer, u32 addr, u32 size)
{

    if (sec == NULL) {
        return E_ERR;
    }

    if (sec->sections == NULL) {
        return E_ERR;
    }

    section_entry* temp = sec->sections;
    while (temp != NULL) {
        if (addr >= temp->v_addr && addr < temp->v_addr + temp->v_size) {
            break;
        }
        temp = temp->next;
    }
    return memcpy_from_buffer(NULL, buffer, temp, size);
}

u32 reset_address_of_sections(section* sec)
{
    // reset address member to 0

    section_entry* temp = sec->sections;
    while (temp != NULL) {
        temp->a_size = 0;
        temp = temp->next;
    }

    return E_OK;
}

u32 fini_section(section* sec)
{
    // destroy section list

    section_entry* temp = sec->sections;
    section_entry* prev = NULL;

    while (temp != NULL) {
        prev = temp;
        temp = temp->next;
        fini_section_entry(prev);
    }
    sec->sections = NULL;
    free(sec->errors);
    free(sec);
    sec = NULL;
    return E_OK;
}

#ifdef __cplusplus
}
#endif
