#include "hnm.h"

/**
 * read_section_headers - reads section headers from ELF file
 * @fd: file descriptor
 * @elf_header: ELF header structure
 * Return: 0 on success, -1 on error
 */
int read_section_headers(int fd, elf_t *elf_header)
{
	int i;

	if (IS_32(elf_header->e64))
	{
		size_t size = sizeof(Elf32_Shdr) * elf_header->e32.e_shnum;

		elf_header->s32 = malloc(size);
		if (!elf_header->s32)
			return (-1);

		lseek(fd, elf_header->e32.e_shoff, SEEK_SET);
		if (read(fd, elf_header->s32, size) != (ssize_t)size)
		{
			free(elf_header->s32);
			elf_header->s32 = NULL;
			return (-1);
		}

		if (IS_BIG_ENDIAN(elf_header->e64))
		{
			for (i = 0; i < elf_header->e32.e_shnum; i++)
			{
				elf_header->s32[i].sh_name = swap_32(elf_header->s32[i].sh_name);
				elf_header->s32[i].sh_type = swap_32(elf_header->s32[i].sh_type);
				elf_header->s32[i].sh_flags = swap_32(elf_header->s32[i].sh_flags);
				elf_header->s32[i].sh_addr = swap_32(elf_header->s32[i].sh_addr);
				elf_header->s32[i].sh_offset = swap_32(elf_header->s32[i].sh_offset);
				elf_header->s32[i].sh_size = swap_32(elf_header->s32[i].sh_size);
				elf_header->s32[i].sh_link = swap_32(elf_header->s32[i].sh_link);
				elf_header->s32[i].sh_info = swap_32(elf_header->s32[i].sh_info);
				elf_header->s32[i].sh_addralign = swap_32(elf_header->s32[i].sh_addralign);
				elf_header->s32[i].sh_entsize = swap_32(elf_header->s32[i].sh_entsize);
			}
		}
	}
	else
	{
		size_t size = sizeof(Elf64_Shdr) * elf_header->e64.e_shnum;

		elf_header->s64 = malloc(size);
		if (!elf_header->s64)
			return (-1);

		lseek(fd, elf_header->e64.e_shoff, SEEK_SET);
		if (read(fd, elf_header->s64, size) != (ssize_t)size)
		{
			free(elf_header->s64);
			elf_header->s64 = NULL;
			return (-1);
		}

		if (IS_BIG_ENDIAN(elf_header->e64))
		{
			for (i = 0; i < elf_header->e64.e_shnum; i++)
			{
				elf_header->s64[i].sh_name = swap_64(elf_header->s64[i].sh_name);
				elf_header->s64[i].sh_type = swap_64(elf_header->s64[i].sh_type);
				elf_header->s64[i].sh_flags = swap_64(elf_header->s64[i].sh_flags);
				elf_header->s64[i].sh_addr = swap_64(elf_header->s64[i].sh_addr);
				elf_header->s64[i].sh_offset = swap_64(elf_header->s64[i].sh_offset);
				elf_header->s64[i].sh_size = swap_64(elf_header->s64[i].sh_size);
				elf_header->s64[i].sh_link = swap_64(elf_header->s64[i].sh_link);
				elf_header->s64[i].sh_info = swap_64(elf_header->s64[i].sh_info);
				elf_header->s64[i].sh_addralign = swap_64(elf_header->s64[i].sh_addralign);
				elf_header->s64[i].sh_entsize = swap_64(elf_header->s64[i].sh_entsize);
			}
		}
	}
	return (0);
}

/**
 * find_symtab_section - finds the symbol table section
 * @elf_header: ELF header structure
 * Return: index of symbol table section, -1 if not found
 */
int find_symtab_section(elf_t *elf_header)
{
	int i;

	if (IS_32(elf_header->e64))
		for (i = 0; i < elf_header->e32.e_shnum; i++)
			if (elf_header->s32[i].sh_type == SHT_SYMTAB)
				return (i);

	for (i = 0; i < elf_header->e64.e_shnum; i++)
		if (elf_header->s64[i].sh_type == SHT_SYMTAB)
			return (i);
	return (-1);
}
