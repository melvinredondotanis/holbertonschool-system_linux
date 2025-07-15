#ifndef HNM_H
#define HNM_H

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define USAGE "Usage: hnm [objfile ...]\n"

#define ERR_PREFIX "%s: "
#define ERR_NO_ENTRY \
	ERR_PREFIX       \
	"'%s': No such file\n"
#define ERR_NO_ACCESS \
	ERR_PREFIX        \
	"%s: Permission denied\n"
#define ERR_NOT_MAGIC \
	ERR_PREFIX        \
	"%s: File format not recognized\n"

#define IS_32(x) ((x).e_ident[EI_CLASS] == ELFCLASS32)
#define IS_BIG_ENDIAN(x) ((x).e_ident[EI_DATA] == ELFDATA2MSB)

/**
 * struct Elf - stores 32/64 structs and other data
 * @e64: the 64 bit struct
 * @e32: the 32 bit struct
 * @s64: the 64 bit struct section array
 * @s32: the 32 bit struct section array
 * @p64: the 64 bit struct program array
 * @p32: the 32 bit struct program array
 * @y64: the 64 bit struct symbol array
 * @y32: the 32 bit struct symbol array
 * @strtab: the string table
 */
typedef struct Elf
{
	Elf64_Ehdr e64;
	Elf32_Ehdr e32;
	Elf64_Shdr *s64;
	Elf32_Shdr *s32;
	Elf64_Phdr *p64;
	Elf32_Phdr *p32;
	Elf64_Sym *y64;
	Elf32_Sym *y32;
	char *strtab;
} elf_t;

int read_section_headers(int fd, elf_t *elf_header);
int find_symtab_section(elf_t *elf_header);

uint32_t swap_32(uint32_t value);
uint64_t swap_64(uint64_t value);

char get_symbol_type_64(Elf64_Sym *sym, elf_t *elf_header);
char get_symbol_type_32(Elf32_Sym *sym, elf_t *elf_header);

int displays_symbols(char *filename, char *program_name);
void print_symbols_32(int fd, elf_t *elf_header, int symtab_idx);
void print_symbols_64(int fd, elf_t *elf_header, int symtab_idx);

#endif /* HNM_H */
