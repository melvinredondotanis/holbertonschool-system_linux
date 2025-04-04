#include "hls.h"

/**
 * parse_options - Parse command line options
 * @argc: Pointer to the number of command line arguments
 * @argv: The command line arguments
 * @options: Struct to store options
 */
static void parse_options(int *argc, char *argv[], struct options *options)
{
	int i, j, k;

	for (i = 1; i < *argc; i++)
	{
		if (argv[i][0] != '-' || argv[i][1] == '\0')
			continue;

		for (j = 1; argv[i][j] != '\0'; j++)
		{
			switch (argv[i][j])
			{
				case '1':
					options->display_one_per_line = 1;
					break;
				case 'a':
					options->show_hidden = 1;
					break;
				case 'A':
					options->show_almost_all = 1;
					break;
				case 'l':
					options->detailed_listing = 1;
					break;
				default:
					fprintf(stderr, "%s: invalid option -- '%c'\n",
							argv[0], argv[i][j]);
					exit(2);
			}
		}

		for (k = i; k < *argc - 1; k++)
			argv[k] = argv[k + 1];
		(*argc)--;
		i--;
	}
}

/**
 * process_single_dir - Process a single directory
 * @dir: Directory to process
 * @pn: Program name
 * @ac: The number of command line arguments
 * @op: Struct to store options
 * Return: void
 */
static void process_single_dir(char *dir, char *pn, int ac, struct options op)
{
	struct entry_list list;

	list.head = NULL;
	list.count = 0;
	list_files(dir, pn, ac, op.display_one_per_line,
			   op.show_hidden, op.show_almost_all,
			   op.detailed_listing, &list);
	free_entry_list(&list);
}

/**
 * main - Entry point of the program.
 * @argc: The number of command line arguments.
 * @argv: The command line arguments.
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[])
{
	struct options options = {0, 0, 0, 0};
	int i, files_listed = 0;

	parse_options(&argc, argv, &options);

	if (argc == 1)
	{
		process_single_dir(".", argv[0], argc, options);
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			if (i > 1 && argv[i][0] != '-')
				printf("\n");

			process_single_dir(argv[i], argv[0], argc, options);

			if (i < argc - 1)
			{
				if (files_listed)
					printf(" ");
				files_listed = 1;
			}
		}
	}
	return (0);
}
