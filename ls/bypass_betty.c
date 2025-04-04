#include "hls.h"

/**
 * free_entry_list - Function to free the memory allocated for the linked list.
 * @list: Pointer to the EntryList to be freed.
 * Return: void
 */
void free_entry_list(struct entry_list *list)
{
	struct entry *current = list->head;

	while (current != NULL)
	{
		struct entry *next = current->next;

		free(current);
		current = next;
	}
	list->head = NULL;
	list->count = 0;
}

/**
 * print_time - Function to print the modification time of a file.
 * @mod_time: The modification time of the file.
 * Return: void
 */
void print_time(time_t mod_time)
{
	char *mod_time_str = ctime(&mod_time);
	char formated_month[4];
	char formated_day[3];
	char formated_hour[3];
	char formated_minute[3];

	formated_month[3] = '\0';
	formated_month[0] = mod_time_str[4];
	formated_month[1] = mod_time_str[5];
	formated_month[2] = mod_time_str[6];

	formated_day[2] = '\0';
	formated_day[0] = mod_time_str[8];
	formated_day[1] = mod_time_str[9];

	formated_hour[2] = '\0';
	formated_hour[0] = mod_time_str[11];
	formated_hour[1] = mod_time_str[12];

	formated_minute[2] = '\0';
	formated_minute[0] = mod_time_str[14];
	formated_minute[1] = mod_time_str[15];

	printf("%s %s %s:%s", formated_month, formated_day,
		   formated_hour, formated_minute);
}

/**
 * add_entry - Function to add an entry to the linked list.
 * @l: Pointer to the EntryList to which the entry will be added.
 * @n: The name of the file or directory.
 * @st_m: The mode of the file or directory.
 * @h: Flag indicating if the entry is hidden (1) or not (0).
 * Return: void
 */
void add_entry(struct entry_list *l, const char *n, mode_t st_m, int h)
{
	struct entry *new_entry = (struct entry *)malloc(sizeof(struct entry));

	if (new_entry == NULL)
	{
		perror("malloc");
		exit(2);
	}

	_strcpy(new_entry->name, n);
	new_entry->st_mode = st_m;
	new_entry->is_hidden = h;
	new_entry->next = l->head;
	l->head = new_entry;
	l->count++;
}

/**
 * handle_list_output - Handle the output of the file list
 * @list: Pointer to the entry list
 * @path: Path being processed
 * @pn: Program name
 * @opl: One per line flag
 * @detailed_listing: Detailed listing flag
 */
void handle_list_output(struct entry_list *list, const char *path,
						const char *pn, int opl, int detailed_listing)
{
	struct entry *current = list->head;

	if (detailed_listing)
	{
		handle_detailed_listing(list, path, pn);
		return;
	}

	while (current != NULL)
	{
		printf("%s%s", current->name,
			   (opl || !current->next) ? "\n" : "  ");
		current = current->next;
	}
}

/**
 * should_process_entry - Determine if an entry should be processed
 * @n: Name of the entry
 * @show_hidden: Flag to show hidden files
 * @show_almost_all: Flag to show almost all files
 * Return: 1 if entry should be processed, 0 otherwise
 */
int should_process_entry(const char *n, int show_hidden, int show_almost_all)
{
	if (n[0] != '.')
		return (2);
	if (show_hidden)
		return (2);
	if (show_almost_all &&
		_strcmp(n, ".") != 0 &&
		_strcmp(n, "..") != 0)
		return (2);
	return (0);
}
