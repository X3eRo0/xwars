#include "Common.hpp"

// global reader and writer ends
static FILE *reader_e, *writer_e;
// pipe fds
static int terminal_pipes[2];

void SetupPipe()
{
    if (pipe(terminal_pipes) != 0) {
        printf("[!] Failed to allocate pipes\n");
    }

    reader_e = fdopen(terminal_pipes[0], "r");
    writer_e = fdopen(terminal_pipes[1], "w");

    if (reader_e == NULL || writer_e == NULL) {
        printf("[!] Failed to allocate pipes\n");
    }

    printf("[+] Pipes Allocated\n");
}

FILE* get_reader_end()
{
    if (reader_e == NULL) {
        SetupPipe();
    }
    return reader_e;
}

FILE* get_writer_end()
{
    if (writer_e == NULL) {
        SetupPipe();
    }
    return writer_e;
}
