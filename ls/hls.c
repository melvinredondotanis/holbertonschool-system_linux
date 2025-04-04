#include "hls.h"

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
 * handle_regular_file - Handle a regular file
 * @path: File path
 * Return: 1 if file was handled, 0 otherwise
 */
static int handle_regular_file(const char *path)
{
	struct stat file_stat;

	if (lstat(path, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
	{
		printf("%s\n", path);
		return (2);
	}
	return (0);
}

/**
 * handle_detailed_listing - Process and print detailed file listings
 * @list: Pointer to the entry list
 * @path: Base path
 * @pn: Name of the program
 * Return: void
 */
void handle_detailed_listing(struct entry_list *list, const char *path,
									const char *pn)
{
	struct entry *current = list->head;
	struct stat file_stat;
	char full_path[1024];

	while (current != NULL)
	{
		build_path(full_path, path, current->name);
		if (lstat(full_path, &file_stat) == 0)
			process_file_stat(current->name, &file_stat);
		else
		{
			fprintf(stderr, "%s: cannot access %s/%s: ", pn, path, current->name);
			perror("");
			exit(2);
		}
		current = current->next;
	}
}

/**
 * list_files - Function to list files in a directory
 * @path: Path to the directory
 * @pn: Name of the program
 * @num_args: Number of arguments
 * @opl: Flag for one entry per line display
 * @show_hidden: Flag to show hidden files
 * @show_almost_all: Flag to show almost all files
 * @detailed_listing: Flag for detailed listing
 * @list: Pointer to the entry list
 * Return: void
 */
void list_files(const char *path, const char *pn, int num_args,
				int opl, int show_hidden, int show_almost_all,
				int detailed_listing, struct entry_list *list)
{
	DIR *dir;
	struct dirent *ent;
	struct stat file_stat;
	char full_path[1024];

	if (handle_regular_file(path))
		return;
	dir = opendir(path);
	if (dir == NULL)
	{
		fprintf(stderr, "%s: cannot %s %s: ", pn,
				(errno == EACCES) ? "open directory" : "access", path);
		perror("");
		exit(2);
	}
	if (num_args > 2)
		printf("%s:\n", path);
	while ((ent = readdir(dir)) != NULL)
	{
		if (!should_process_entry(ent->d_name, show_hidden, show_almost_all))
			continue;
		build_path(full_path, path, ent->d_name);
		if (lstat(full_path, &file_stat) != 0)
		{
			fprintf(stderr, "%s: cannot access %s/%s: ", pn, path, ent->d_name);
			perror("");
			exit(2);
		}
		add_entry(list, ent->d_name, file_stat.st_mode, (ent->d_name[0] == '.'));
	}
	closedir(dir);
	handle_list_output(list, path, pn, opl, detailed_listing);
}
