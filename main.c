#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
    {"help",    no_argument, 0, 'h'}
};

#define PRGM_VERSION "0.0.1"

void print_version();

int main(int argc, char **argv)
{
    int     c, fsize;
    uint8_t *buffer;
    FILE    *fp;

    c = getopt_long(argc, argv, "vh", long_options, NULL);
    if (c != -1)
        switch (c) {
            case 'v': // --version
                print_version();
                exit(EXIT_SUCCESS);
            case 'h': // --help
                printf("usage: %s [--version] [--help] <file_path>\n", argv[0]);
                exit(EXIT_SUCCESS);
            default: // unknown
                fprintf(stderr, "usage: %s [--version] [--help] <file_path>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

    fp = fopen(argv[1], "rb");
    if (fp == NULL)
        fprintf(stderr, "error: could not open file '%s'\n", argv[1]);

    // determine file size
    fseek(fp, 0L, SEEK_END); // seek to end of file
    fsize = ftell(fp);       // position is size of file
    rewind(fp);              // seek to start of file

    buffer = malloc(fsize);
    fread(buffer, fsize, 1, fp);

    fclose(fp);

    int i;
    for (i = 0; i < fsize; i++)
        printf("%02X\n", buffer[i]);

    return 0;
}

void print_version()
{
    printf("version %s\n", PRGM_VERSION);
}
