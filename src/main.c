#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

#include "include/disassembler.h"

#define PRGM_NAME    "disassemble"
#define PRGM_VERSION "0.1"
#define USAGE        "usage: %s [--version] [--help] <file_path>\n"

static struct option long_options[] = {
	{"version", no_argument, 0, 'v'},
	{"help",    no_argument, 0, 'h'}
};

int main(int argc, char *argv[])
{
	int     c, fsize, i, j;
	uint8_t *buffer, opbytes;
	FILE    *fp;

	c = getopt_long(argc, argv, "vh", long_options, NULL);
	switch (c) {
	case -1:
		if (argv[1])
			break;
		fprintf(stderr, USAGE, PRGM_NAME);
		exit(EXIT_SUCCESS);
	case 'v': /* --version */
		printf("%s verson %s", PRGM_NAME, PRGM_VERSION);
		exit(EXIT_SUCCESS);
	case 'h': /* --help */
		printf(USAGE, PRGM_NAME);
		exit(EXIT_SUCCESS);
	default: /* unknown */
		fprintf(stderr, USAGE, PRGM_NAME);
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		fprintf(stderr, "error: could not open file '%s'\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// determine file size
	fseek(fp, 0L, SEEK_END); // seek to end of file
	fsize = ftell(fp);       // position is size of file
	rewind(fp);              // seek to start of file

	buffer = malloc(fsize);
	if (buffer == NULL) {
		fprintf(stderr, "%s: failed to allocate memory", PRGM_NAME);
		exit(errno);
	}
	fread(buffer, fsize, 1, fp);

	fclose(fp);

	struct instruction op;
	for (i = 0, opbytes = 0; i < fsize; i += opbytes) {
		op = instruction_for_value(buffer[i]);
		opbytes = op.len;

		printf("%s", op.name);

		if (opbytes > 1)
		for (j = 1; j < opbytes; j++)
                printf("%02X ", buffer[i+j]);
        printf("\n");
    }
    
    free(buffer);

    return 0;
}
