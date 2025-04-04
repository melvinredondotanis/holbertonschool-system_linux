#ifndef HLS_H
#define HLS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#include <pwd.h>
#include <time.h>

/**
 * struct entry - Structure to hold a single entry in the linked list.
 * @name: Name of the file or directory.
 * @st_mode: Mode of the file or directory.
 * @is_hidden: Flag indicating if the entry is hidden (1) or not (0).
 * @next: Pointer to the next entry in the linked list.
 */
struct entry
{
	char			name[256];
	mode_t			st_mode;
	int				is_hidden;
	struct entry	*next;
};

/**
 * struct entry_list - Structure to hold a linked list of entries.
 * @head: Pointer to the head of the list.
 * @count: Number of entries in the list.
 */
struct entry_list
{
	struct entry	*head;
	int				count;
};

/**
 * struct options - Structure to hold command line options.
 * @display_one_per_line: Flag for displaying one entry per line.
 * @show_hidden: Flag for showing hidden files.
 * @show_almost_all: Flag for showing almost all files.
 * @detailed_listing: Flag for detailed listing.
 */
struct options
{
	int				display_one_per_line;
	int				show_hidden;
	int				show_almost_all;
	int				detailed_listing;
};

/* strings */
size_t				_strlen(const char *str);
char				*_strcpy(char *dest, const char *src);

/* hls */
void				list_files(const char *path, const char *program_name, int num_args,
								int display_one_per_line, int show_hidden,
								int show_almost_all, int detailed_listing,
								struct entry_list *list);
void				add_entry_to_list(struct entry_list *list, const char *name,
								mode_t st_mode, int is_hidden);
void				free_entry_list(struct entry_list *list);

#endif /* HLS_H */