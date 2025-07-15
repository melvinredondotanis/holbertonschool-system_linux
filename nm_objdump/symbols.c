#include "hnm.h"

/**
 * get_symbol_type_64 - determines symbol type for 64-bit ELF
 * @sym: symbol structure
 * @elf_header: ELF header structure
 * Return: character representing symbol type
 */
char get_symbol_type_64(Elf64_Sym *sym, elf_t *elf_header)
{
	unsigned char bind = ELF64_ST_BIND(sym->st_info);

	if (bind == STB_WEAK)
	{
		if (sym->st_shndx == SHN_UNDEF)
			return ('w');
		else
			return ('W');
	}

	if (sym->st_shndx == SHN_UNDEF)
		return ('U');

	if (sym->st_shndx == SHN_ABS)
		return (bind == STB_LOCAL ? 'a' : 'A');

	if (sym->st_shndx < elf_header->e64.e_shnum)
	{
		Elf64_Shdr *shdr = &elf_header->s64[sym->st_shndx];

		if (shdr->sh_type == SHT_PROGBITS)
		{
			if (shdr->sh_flags & SHF_EXECINSTR)
				return (bind == STB_LOCAL ? 't' : 'T');
			if (shdr->sh_flags & SHF_WRITE)
				return (bind == STB_LOCAL ? 'd' : 'D');
			return (bind == STB_LOCAL ? 'r' : 'R');
		}
		if (shdr->sh_type == SHT_NOBITS)
			return (bind == STB_LOCAL ? 'b' : 'B');
		if (shdr->sh_type == SHT_DYNAMIC)
			return (bind == STB_LOCAL ? 'd' : 'D');
	}

	return ('?');
}

/**
 * get_symbol_type_32 - determines symbol type for 32-bit ELF
 * @sym: symbol structure
 * @elf_header: ELF header structure
 * Return: character representing symbol type
 */
char get_symbol_type_32(Elf32_Sym *sym, elf_t *elf_header)
{
	unsigned char bind = ELF32_ST_BIND(sym->st_info);

	if (bind == STB_WEAK)
	{
		if (sym->st_shndx == SHN_UNDEF)
			return ('w');
		else
			return ('W');
	}

	if (sym->st_shndx == SHN_UNDEF)
		return ('U');

	if (sym->st_shndx == SHN_ABS)
		return (bind == STB_LOCAL ? 'a' : 'A');

	if (sym->st_shndx < elf_header->e32.e_shnum)
	{
		Elf32_Shdr *shdr = &elf_header->s32[sym->st_shndx];

		if (shdr->sh_type == SHT_PROGBITS)
		{
			if (shdr->sh_flags & SHF_EXECINSTR)
				return (bind == STB_LOCAL ? 't' : 'T');
			if (shdr->sh_flags & SHF_WRITE)
				return (bind == STB_LOCAL ? 'd' : 'D');
			return (bind == STB_LOCAL ? 'r' : 'R');
		}
		if (shdr->sh_type == SHT_NOBITS)
			return (bind == STB_LOCAL ? 'b' : 'B');
	}

	return ('?');
}

/**
 * print_symbols_32 - prints symbols from 32-bit ELF file
 * @fd: file descriptor
 * @elf_header: ELF header structure
 * @symtab_idx: index of symbol table section
 */
void print_symbols_32(int fd, elf_t *elf_header, int symtab_idx)
{
	int i, num_symbols, strtab_idx;
	char *strtab;
	size_t strtab_size;

	strtab_idx = elf_header->s32[symtab_idx].sh_link;
	strtab_size = elf_header->s32[strtab_idx].sh_size;
	strtab = malloc(strtab_size);
	if (!strtab)
		return;

	lseek(fd, elf_header->s32[strtab_idx].sh_offset, SEEK_SET);
	read(fd, strtab, strtab_size);

	num_symbols = elf_header->s32[symtab_idx].sh_size / sizeof(Elf32_Sym);
	elf_header->y32 = malloc(elf_header->s32[symtab_idx].sh_size);
	if (!elf_header->y32)
	{
		free(strtab);
		return;
	}

	lseek(fd, elf_header->s32[symtab_idx].sh_offset, SEEK_SET);
	read(fd, elf_header->y32, elf_header->s32[symtab_idx].sh_size);

	if (IS_BIG_ENDIAN(elf_header->e64))
		for (i = 0; i < num_symbols; i++)
		{
			elf_header->y32[i].st_name = swap_32(elf_header->y32[i].st_name);
			elf_header->y32[i].st_value = swap_32(elf_header->y32[i].st_value);
			elf_header->y32[i].st_size = swap_32(elf_header->y32[i].st_size);
			elf_header->y32[i].st_shndx = (swap_32(elf_header->y32[i].st_shndx) >> 16) & 0xFFFF;
		}

	for (i = 0; i < num_symbols; i++)
	{
		Elf32_Sym *sym = &elf_header->y32[i];
		char type;

		if (sym->st_name == 0 || ELF32_ST_TYPE(sym->st_info) == STT_FILE)
			continue;

		type = get_symbol_type_32(sym, elf_header);
		if (sym->st_shndx == SHN_UNDEF || type == 'U')
			printf("         %c %s\n", type, &strtab[sym->st_name]);
		else if (sym->st_value == 0)
			printf("         %c %s\n", type, &strtab[sym->st_name]);
		else
			printf("%08x %c %s\n", sym->st_value, type, &strtab[sym->st_name]);
	}

	free(strtab);
}

/**
 * print_symbols_64 - prints symbols from 64-bit ELF file
 * @fd: file descriptor
 * @elf_header: ELF header structure
 * @symtab_idx: index of symbol table section
 */
void print_symbols_64(int fd, elf_t *elf_header, int symtab_idx)
{
	int i, num_symbols, strtab_idx;
	char *strtab;
	size_t strtab_size;

	strtab_idx = elf_header->s64[symtab_idx].sh_link;
	strtab_size = elf_header->s64[strtab_idx].sh_size;
	strtab = malloc(strtab_size);
	if (!strtab)
		return;

	lseek(fd, elf_header->s64[strtab_idx].sh_offset, SEEK_SET);
	read(fd, strtab, strtab_size);

	num_symbols = elf_header->s64[symtab_idx].sh_size / sizeof(Elf64_Sym);
	elf_header->y64 = malloc(elf_header->s64[symtab_idx].sh_size);
	if (!elf_header->y64)
	{
		free(strtab);
		return;
	}

	lseek(fd, elf_header->s64[symtab_idx].sh_offset, SEEK_SET);
	read(fd, elf_header->y64, elf_header->s64[symtab_idx].sh_size);

	for (i = 0; i < num_symbols; i++)
	{
		Elf64_Sym *sym = &elf_header->y64[i];
		char type;

		if (sym->st_name == 0 || ELF64_ST_TYPE(sym->st_info) == STT_FILE)
			continue;

		type = get_symbol_type_64(sym, elf_header);
		if (sym->st_value == 0)
			printf("                 %c %s\n", type, &strtab[sym->st_name]);
		else
			printf("%016lx %c %s\n", sym->st_value, type, &strtab[sym->st_name]);
	}

	free(strtab);
}
