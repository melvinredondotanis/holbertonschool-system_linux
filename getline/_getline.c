#include "_getline.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * free_all_buffers - Frees all buffer nodes
 * @head: Pointer to the head of the linked list
 * Return: NULL
 */
void *free_all_buffers(fd_buffer_t *head)
{
	fd_buffer_t *temp_node;

	while (head)
	{
		temp_node = head;
		head = head->next;
		free(temp_node);
	}
	return (NULL);
}

/**
 * find_or_create_buffer - Finds a buffer for the fd or creates a new one
 * @head: Pointer to the head of the buffer list
 * @fd: File descriptor to find or create
 * Return: Pointer to the buffer node, or NULL on failure
 */
fd_buffer_t *find_or_create_buffer(fd_buffer_t **head, const int fd)
{
	fd_buffer_t *current = NULL, *prev = NULL;

	for (current = *head; current && current->fd != fd;
		 prev = current, current = current->next)
		;

	if (!current)
	{
		current = malloc(sizeof(fd_buffer_t));
		if (!current)
			return (NULL);

		current->fd = fd;
		current->buffer_pos = 0;
		current->bytes_read = 0;
		current->next = NULL;

		if (!*head)
			*head = current;
		else if (prev)
			prev->next = current;
	}

	return (current);
}

/**
 * read_buffer - Reads data into the buffer if needed
 * @current: Current buffer node
 * Return: 1 on success, 0 on EOF or error
 */
int read_buffer(fd_buffer_t *current)
{
	if (current->buffer_pos >= current->bytes_read)
	{
		current->bytes_read = read(current->fd, current->buffer, READ_SIZE);
		if (current->bytes_read <= 0)
			return (0);

		current->buffer_pos = 0;
	}
	return (1);
}

/**
 * extract_line - Extracts a line from the buffer
 * @current: Current buffer node
 * @line: Pointer to the line being built
 * @line_size: Current size of the line
 * Return: Updated line or NULL on failure
 */
char *extract_line(fd_buffer_t *current, char *line, int *line_size)
{
	int new_line_pos, i;
	char *temp;

	for (new_line_pos = current->buffer_pos;
		 new_line_pos < current->bytes_read && current->buffer[new_line_pos] != '\n';
		 new_line_pos++)
		;

	temp = realloc(line, *line_size + (new_line_pos - current->buffer_pos) + 1);
	if (!temp)
	{
		free(line);
		return (NULL);
	}

	line = temp;

	for (i = 0; current->buffer_pos < new_line_pos; i++)
		line[*line_size + i] = current->buffer[current->buffer_pos++];

	line[*line_size + i] = '\0';
	*line_size += i;

	if (new_line_pos < current->bytes_read &&
		current->buffer[new_line_pos] == '\n')
	{
		current->buffer_pos++;
		return (line);
	}

	return (line);
}

/**
 * _getline - Reads a line from a file descriptor
 * @fd: The file descriptor to read from
 * Return: A pointer to the line read, or NULL on failure or EOF
 */
char *_getline(const int fd)
{
	static fd_buffer_t *head;
	fd_buffer_t *current = NULL;
	char *line = NULL;
	int line_size = 0;

	if (fd == -1)
		return (free_all_buffers(head));

	if (fd < 0)
		return (NULL);

	current = find_or_create_buffer(&head, fd);
	if (!current)
		return (NULL);

	while (1)
	{
		if (!read_buffer(current))
			return (line_size > 0 ? line : NULL);

		line = extract_line(current, line, &line_size);
		if (!line)
			return (NULL);

		if (current->buffer_pos > 0 &&
			current->buffer_pos <= current->bytes_read &&
			current->buffer[current->buffer_pos - 1] == '\n')
			return (line);
	}
}
