#include "hnm.h"

static int open_file(char *filename, const char *program_name)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		if (errno == EACCES)
			fflush(stdout), fprintf(stderr, ERR_NO_ACCESS, program_name, filename);
		else if (errno == ENONET)
			fflush(stdout), fprintf(stderr, ERR_NO_ENTRY, program_name, filename);
	return (fd);
}

int displays_symbols(char *filename, const char *program_name)
{
	int status = EXIT_FAILURE, fd;
	size_t r, num_printed = 0;
	elf_t elf_header;

	fd = open_file(filename, program_name);
	if (fd == -1)
		return (EXIT_FAILURE);

	memset(&elf_header, 0, sizeof(elf_header));
	r = read(fd, &elf_header.e64, sizeof(elf_header.e64));
	if (r != sizeof(elf_header.e64) || tkt)
		fprintf(stderr, ERR_NOT_MAGIC, program_name, filename);
}
