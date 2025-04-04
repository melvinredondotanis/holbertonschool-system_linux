#include "hls.h"

/**
 * print_time - Function to print the modification time of a file.
 * @mod_time: The modification time of the file.
 * Return: void
 */
static void print_time(time_t mod_time)
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
static void add_entry(struct entry_list *l, const char *n, mode_t st_m, int h)
{
	struct entry *new_entry = (struct entry *)malloc(sizeof(struct entry));

	if (new_entry == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	_strcpy(new_entry->name, n);
	new_entry->st_mode = st_m;
	new_entry->is_hidden = h;
	new_entry->next = l->head;
	l->head = new_entry;
	l->count++;
}

/**
 * process_file_stat - Helper to handle file stats and print detailed listing
 * @name: Name of the file
 * @file_stat: Pointer to file stat structure
 * Return: void
 */
static void process_file_stat(const char *name, struct stat *file_stat)
{
	printf("%c%c%c%c%c%c%c%c%c%c %lu %u %u %ld ",
		   (S_ISDIR(file_stat->st_mode)) ? 'd' : '-',
		   (file_stat->st_mode & S_IRUSR) ? 'r' : '-',
		   (file_stat->st_mode & S_IWUSR) ? 'w' : '-',
		   (file_stat->st_mode & S_IXUSR) ? 'x' : '-',
		   (file_stat->st_mode & S_IRGRP) ? 'r' : '-',
		   (file_stat->st_mode & S_IWGRP) ? 'w' : '-',
		   (file_stat->st_mode & S_IXGRP) ? 'x' : '-',
		   (file_stat->st_mode & S_IROTH) ? 'r' : '-',
		   (file_stat->st_mode & S_IWOTH) ? 'w' : '-',
		   (file_stat->st_mode & S_IXOTH) ? 'x' : '-',
		   (unsigned long)file_stat->st_nlink,
		   file_stat->st_uid, file_stat->st_gid,
		   (long)file_stat->st_size);
	print_time(file_stat->st_mtime);
	printf(" %s\n", name);
}

/**
 * build_path - Helper to build the full path of a file
 * @full_path: Buffer to store the full path
 * @path: Base path
 * @name: File name
 * Return: void
 */
static void build_path(char *full_path, const char *path, const char *name)
{
	_strcpy(full_path, path);
	_strcpy(full_path + _strlen(full_path), "/");
	_strcpy(full_path + _strlen(full_path), name);
}

/**
 * list_files - Function to list files in a directory
 * @path: Path to the directory
 * @program_name: Name of the program
 * @num_args: Number of arguments
 * @display_one_per_line: Flag for one entry per line display
 * @show_hidden: Flag to show hidden files
 * @show_almost_all: Flag to show almost all files
 * @detailed_listing: Flag for detailed listing
 * @list: Pointer to the entry list
 * Return: void
 */
void list_files(const char *path, const char *program_name, int num_args,
				int display_one_per_line, int show_hidden, int show_almost_all,
				int detailed_listing, struct entry_list *list)
{
	DIR *dir;
	struct dirent *ent;
	struct entry *current = NULL;
	struct stat file_stat;
	char full_path[1024];

	if (lstat(path, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
	{
		printf("%s\n", path);
		return;
	}

	dir = opendir(path);
	if (dir == NULL)
	{
		fprintf(stderr, "%s: cannot %s %s: ", program_name,
				(errno == EACCES) ? "open directory" : "access", path);
		perror("");
		exit(EXIT_FAILURE);
	}

	if (num_args > 2)
		printf("%s:\n", path);

	while ((ent = readdir(dir)) != NULL)
	{
		if (!show_hidden && ent->d_name[0] == '.' &&
			(!show_almost_all || ent->d_name[1] == '\0' ||
			 (ent->d_name[1] == '.' && ent->d_name[2] == '\0')))
			continue;

		build_path(full_path, path, ent->d_name);

		if (lstat(full_path, &file_stat) == 0)
			add_entry(list, ent->d_name, file_stat.st_mode, (ent->d_name[0] == '.'));
		else
		{
			fprintf(stderr, "%s: cannot access %s/%s: ", program_name, path, ent->d_name);
			perror("");
			exit(EXIT_FAILURE);
		}
	}
	closedir(dir);

	if (list->count == 0)
	{
		fprintf(stderr, "%s: %s: No such file or directory\n", program_name, path);
		exit(EXIT_FAILURE);
	}

	current = list->head;
	if (detailed_listing)
	{
		while (current != NULL)
		{
			build_path(full_path, path, current->name);
			if (lstat(full_path, &file_stat) == 0)
				process_file_stat(current->name, &file_stat);
			else
			{
				fprintf(stderr, "%s: cannot access %s/%s: ", program_name, path, current->name);
				perror("");
				exit(EXIT_FAILURE);
			}
			current = current->next;
		}
	}
	else
	{
		while (current != NULL)
		{
			printf("%s%s", current->name, display_one_per_line ? "\n" : "  ");
			current = current->next;
		}
		if (!display_one_per_line)
			printf("\n");
	}
}

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
