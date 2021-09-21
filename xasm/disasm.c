//
// Created by X3eRo0 on 5/1/2021.
//

#include "xasm.h"
#include <unistd.h>

const char* mnemonics[] = {
        [XVM_OP_MOV]  = "mov",
        [XVM_OP_MOVB] = "movb",
        [XVM_OP_MOVW] = "movw",
        [XVM_OP_LEA]  = "lea",
        [XVM_OP_NOP]  = "nop",
        [XVM_OP_HLT]  = "hlt",
        [XVM_OP_RET]  = "ret",
        [XVM_OP_CALL] = "call",
        [XVM_OP_SYSC] = "syscall",
        [XVM_OP_LSU]  = "lsu",
        [XVM_OP_RSU]  = "rsu",
        [XVM_OP_ADD]  = "add",
        [XVM_OP_ADDB]  = "addb",
        [XVM_OP_ADDW]  = "addw",
        [XVM_OP_SUB]  = "sub",
        [XVM_OP_SUBB]  = "subb",
        [XVM_OP_SUBW]  = "subw",
        [XVM_OP_MUL]  = "mul",
        [XVM_OP_MULB]  = "mulb",
        [XVM_OP_MULW]  = "mulw",
        [XVM_OP_DIV]  = "div",
        [XVM_OP_DIVB]  = "divb",
        [XVM_OP_DIVW]  = "divw",
        [XVM_OP_XOR]  = "xor",
        [XVM_OP_XORB]  = "xorb",
        [XVM_OP_XORW]  = "xorw",
        [XVM_OP_AND]  = "and",
        [XVM_OP_ANDB]  = "andb",
        [XVM_OP_ANDW]  = "andw",
        [XVM_OP_OR]   = "or",
        [XVM_OP_ORB]   = "orb",
        [XVM_OP_ORW]   = "orw",
        [XVM_OP_NOT]  = "not",
        [XVM_OP_NOTB]  = "notb",
        [XVM_OP_NOTW]  = "notw",
        [XVM_OP_PUSH] = "push",
        [XVM_OP_POP]  = "pop",
        [XVM_OP_XCHG] = "xchg",
        [XVM_OP_INC]  = "inc",
        [XVM_OP_DEC]  = "dec",
        [XVM_OP_CMP]  = "cmp",
        [XVM_OP_CMPB]  = "cmpb",
        [XVM_OP_CMPW]  = "cmpw",
        [XVM_OP_TEST] = "test",
        [XVM_OP_JMP]  = "jmp",
        [XVM_OP_JZ]   = "jz",
        [XVM_OP_JNZ]  = "jnz",
        [XVM_OP_JA]   = "ja",
        [XVM_OP_JB]   = "jb",
        [XVM_OP_JAE]  = "jae",
        [XVM_OP_JBE]  = "jbe",
        [XVM_OP_RJMP] = "rjmp",
        [XVM_OP_RJZ] = "rjz",
        [XVM_OP_RJNZ] = "rjnz",
        [XVM_OP_RJA] = "rja",
        [XVM_OP_RJB] = "rjb",
        [XVM_OP_RJAE] = "rjae",
        [XVM_OP_RJBE] = "rjbe",
};

const char* registers[XVM_NREGS] = {
        [reg_r0] = "$r0",
        [reg_r1] = "$r1",
        [reg_r2] = "$r2",
        [reg_r3] = "$r3",
        [reg_r4] = "$r4",
        [reg_r5] = "$r5",
        [reg_r6] = "$r6",
        [reg_r7] = "$r7",
        [reg_r8] = "$r8",
        [reg_r9] = "$r9",
        [reg_ra] = "$ra",
        [reg_rb] = "$rb",
        [reg_rc] = "$rc",
        [reg_pc] = "$pc",
        [reg_bp] = "$bp",
        [reg_sp] = "$sp",
};

u32 xasm_disassemble_bytes(FILE *fp, xvm_bin * bin, const char * bytecode, u32 len, u32 address, u32 ninstr){
    if (bytecode == NULL || len == 0){
        return E_ERR;
    }

    if (ninstr == 0){
        ninstr = -1;
    }

    u32 pc = 0;
    u32 imm = 0;
    u8 mode = 0;
    u8 mode1 = 0;
    u8 mode2 = 0;
    u8 opcode = 0;
    u8 reg = 0;
    u8 rel_jmp = 0;

    char * temp = NULL;

    for (u32 i = 0; (pc < len) && i < ninstr; i++){
        fprintf(fp, "0x%-14.8X", address+pc);
        opcode = bytecode[pc++];


        if ( (opcode == XVM_OP_RJMP) ||
             (opcode == XVM_OP_RJNZ) ||
             (opcode == XVM_OP_RJAE) ||
             (opcode == XVM_OP_RJBE) ||
             (opcode == XVM_OP_RJA)  ||
             (opcode == XVM_OP_RJB)  ||
             (opcode == XVM_OP_RJZ)
        ){
            rel_jmp = 1;
        }

        mode = bytecode[pc++];
        if (opcode >= sizeof(mnemonics)/sizeof(mnemonics[0])){
            fprintf(fp, "%-10.7s\n", "(bad)");
            continue;
        }

        fprintf(fp, "%-10.7s", mnemonics[opcode]);

        mode1 = (mode >> 0x0) & 0xf;
        mode2 = (mode >> 0x4) & 0xf;

        if (mode1 != ARG_NARG && mode1 != ARG_REGD && mode1 != ARG_IMMD && !(mode1 & ARG_PTRD)){
            fprintf(fp, "%s\n", "(bad)");
            continue;
        }

        if (mode2 != ARG_NARG && mode2 != ARG_REGD && mode2 != ARG_IMMD && !(mode2 & ARG_PTRD)){
            fprintf(fp, "%s\n", "(bad)");
            continue;
        }

        switch(mode1){
            case ARG_NARG: break;
            case ARG_REGD: {
                reg = bytecode[pc++];
                if (reg >= sizeof(registers)/sizeof(registers[0])){
                    fprintf(fp, "%s\n", "(bad)");
                    continue;
                }
                fprintf(fp, "%s", registers[reg]);
                break;
            }
            case ARG_IMMD: {
                imm = *(u32 *)&bytecode[pc];

                if (rel_jmp){
                    imm = address + pc - 2 + (signed int) imm;
                }

                if (bin != NULL) {
                    temp = resolve_symbol_name(bin->x_symtab, imm);
                }

                if (temp == NULL){
                    if (((signed int) imm) < 0){
                        fprintf(fp, "#0x%x", (signed int)imm);
                    } else {
                        fprintf(fp, "#0x%x", imm);
                    }
                } else {
                    fprintf(fp, "%s" , temp);
                }

                pc += sizeof(u32);
                break;
            }
            default:{
                fprintf(fp, "[");
                if (mode1 & ARG_REGD){
                    reg = bytecode[pc++];
                    if (reg >= sizeof(registers)/sizeof(registers[0])){
                        fprintf(fp, "%s\n", "(bad)");
                        continue;
                    }
                    fprintf(fp, "%s", registers[reg]);
                }

                if ((mode1 & ARG_REGD) && (mode1 & ARG_IMMD)){
                    imm = *(u32 *)&bytecode[pc];
                    if (((signed int) imm) < 0 && imm != 0){
                        fprintf(fp, " - ");
                    } else {
                        fprintf(fp, " + ");
                    }
                }

                if (mode1 & ARG_IMMD){
                    imm = *(u32 *)&bytecode[pc];
                    if (bin != NULL) {
                        temp = resolve_symbol_name(bin->x_symtab, imm);
                    }

                    if (temp == NULL){
                        if (((signed int) imm) < 0){
                            fprintf(fp, "#0x%x", (signed int)imm);
                        } else {
                            fprintf(fp, "#0x%x", imm);
                        }
                    } else {
                        fprintf(fp, "%s" , temp);
                    }

                    pc += sizeof(u32);
                    break;
                }
                fprintf(fp, "]");
            }
        }

        if (mode2 != ARG_NARG){
            fprintf(fp, ", ");
        }

        switch(mode2){
            case ARG_NARG: break;
            case ARG_REGD: {
                reg = bytecode[pc++];
                if (reg >= sizeof(registers)/sizeof(registers[0])){
                    fprintf(fp, "%s\n", "(bad)");
                    continue;
                }
                fprintf(fp, "%s", registers[reg]);
                break;
            }
            case ARG_IMMD: {
                imm = *(u32 *)&bytecode[pc];
                if (bin != NULL) {
                    temp = resolve_symbol_name(bin->x_symtab, imm);
                }

                if (temp == NULL){
                    if (((signed int) imm) < 0){
                        fprintf(fp, "#0x%x", (signed int)imm);
                    } else {
                        fprintf(fp, "#0x%x", imm);
                    }
                } else {
                    fprintf(fp, "%s" , temp);
                }

                pc += sizeof(u32);
                break;
            }
            default:{
                fprintf(fp, "[");
                if (mode2 & ARG_REGD){
                    reg = bytecode[pc++];
                    if (reg >= sizeof(registers)/sizeof(registers[0])){
                        fprintf(fp, "%s\n", "(bad)");
                        continue;
                    }
                    fprintf(fp, "%s", registers[reg]);
                }

                if ((mode2 & ARG_REGD) && (mode2 & ARG_IMMD)){
                    imm = *(u32 *)&bytecode[pc];
                    if (((signed int) imm) < 0 && imm != 0){
                        fprintf(fp, " - ");
                    } else {
                        fprintf(fp, " + ");
                    }
                }

                if (mode2 & ARG_IMMD) {
                    imm = *(u32 *) &bytecode[pc];
                    if (bin != NULL) {
                        temp = resolve_symbol_name(bin->x_symtab, imm);
                    }

                    if (temp == NULL) {
                        if (((signed int) imm) < 0) {
                            fprintf(fp, "#0x%x", (signed int) imm);
                        } else {
                            fprintf(fp, "#0x%x", imm);
                        }
                    } else {
                        fprintf(fp, "%s", temp);
                    }

                    pc += sizeof(u32);
                }
                fprintf(fp, "]");
            }
        }
        fprintf(fp, "\n");
    }

}
