#include "hnm.h"

/**
 * free_them - frees all allocated memory for ELF header
 * @elf_header: ELF header structure
 */
static void free_them(elf_t elf_header)
{
	free(elf_header.s32);
	free(elf_header.s64);
	free(elf_header.p32);
	free(elf_header.p64);
	free(elf_header.y32);
	free(elf_header.y64);
	free(elf_header.strtab);
}

/**
 * check_elf - checks if header matches magic bytes
 * @elf_header: 16 byte buffer holding elf header
 * Return: 0 if ELF else 1
 */
static int check_elf(char *elf_header)
{
	return (elf_header[0] == 0x7f &&
			elf_header[1] == 'E' &&
			elf_header[2] == 'L' &&
			elf_header[3] == 'F');
}

/**
 * open_file - opens a file and checks for errors
 * @filename: name of the file to open
 * @program_name: name of the program (for error messages)
 * Return: file descriptor or -1 on error
 */
static int open_file(char *filename, char *program_name)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			fflush(stdout), fprintf(stderr, ERR_NO_ACCESS, program_name, filename);
		else if (errno == ENOENT)
			fflush(stdout), fprintf(stderr, ERR_NO_ENTRY, program_name, filename);
	}
	return (fd);
}

/**
 * verify_elf_header - verifies ELF header and reads appropriate header
 * @fd: file descriptor
 * @elf_header: ELF header structure
 * @program_name: name of the program (for error messages)
 * @filename: name of the file being read
 * Return: 0 on success, -1 on error
 */
static int verify_elf_header(int fd, elf_t *elf_header, char *program_name,
							char *filename)
{
	size_t r;

	r = read(fd, &elf_header->e64, sizeof(elf_header->e64));
	if (r != sizeof(elf_header->e64) || !check_elf((char *)&elf_header->e64))
	{
		fprintf(stderr, ERR_NOT_MAGIC, program_name, filename);
		return (-1);
	}

	if (IS_32(elf_header->e64))
	{
		lseek(fd, 0, SEEK_SET);
		r = read(fd, &elf_header->e32, sizeof(elf_header->e32));
		if (r != sizeof(elf_header->e32) || !check_elf((char *)&elf_header->e32))
		{
			fprintf(stderr, ERR_NOT_MAGIC, program_name, filename);
			return (-1);
		}
	}

	return (0);
}

/**
 * displays_symbols - displays symbols from an ELF file
 * @filename: name of the file to read
 * @program_name: name of the program (for error messages)
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int displays_symbols(char *filename, char *program_name)
{
	int status = EXIT_FAILURE, fd;
	int symtab_idx;
	elf_t elf_header;

	fd = open_file(filename, program_name);
	if (fd == -1)
		return (status);

	memset(&elf_header, 0, sizeof(elf_header));

	if (verify_elf_header(fd, &elf_header, program_name, filename) == -1)
		goto cleanup;

	if (read_section_headers(fd, &elf_header) == -1)
		goto cleanup;

	symtab_idx = find_symtab_section(&elf_header);
	if (symtab_idx == -1)
	{
		status = EXIT_SUCCESS;
		goto cleanup;
	}

	if (IS_32(elf_header.e64))
		print_symbols_32(fd, &elf_header, symtab_idx);
	else
		print_symbols_64(fd, &elf_header, symtab_idx);

	status = EXIT_SUCCESS;

cleanup:
	free_them(elf_header);
	close(fd);
	return (status);
}
