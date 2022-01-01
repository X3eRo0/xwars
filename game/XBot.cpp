#include "XBot.hpp"

// initialize xbot
xbot::xbot()
{
    cpu = init_xvm_cpu();
    bin = init_xvm_bin();
    bot_addr = 0;
    offset = 0;
    size = 0;
    bot_section = NULL;
    pipe(reg_pipes);
    pipe(dis_pipes);

    reg_reader_e = fdopen(reg_pipes[0], "r");
    setbuf(reg_reader_e, NULL);
    reg_writer_e = fdopen(reg_pipes[1], "w");
    setbuf(reg_writer_e, NULL);
    dis_reader_e = fdopen(dis_pipes[0], "r");
    setbuf(dis_reader_e, NULL);
    dis_writer_e = fdopen(dis_pipes[1], "w");
    setbuf(dis_writer_e, NULL);

    if (!reg_reader_e || !reg_writer_e || !dis_reader_e || !dis_writer_e) {
        puts("[!] Failed to allocate pipes for bot");
    }
}

// bot destructor
xbot::~xbot()
{
    if (cpu != nullptr)
        fini_xvm_cpu(cpu);
    if (bin != nullptr)
        fini_xvm_bin(bin);

    cpu = NULL;
    bin = NULL;
    fclose(reg_reader_e);
    fclose(reg_writer_e);
    fclose(dis_reader_e);
    fclose(dis_writer_e);
}

// add a new section to this bot
void xbot::add_section(section_entry* sxn)
{
    section_entry* tmp_sxn = bin->x_section->sections;
    while (tmp_sxn->next != NULL) {
        tmp_sxn = tmp_sxn->next;
    }

    tmp_sxn->next = sxn;
    bin->x_section->n_sections++;
}

u32 xbot::step()
{
    if (cpu && bin) {
        return do_execute(cpu, bin);
    }
    return E_ERR;
}
