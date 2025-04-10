#include "_getline.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * _getline - Reads a line from a file descriptor
 * @fd: The file descriptor to read from
 * Return: A pointer to the line read, or NULL on failure or EOF
 */
char *_getline(const int fd)
{
	static char buffer[READ_SIZE + 1];
	static int buffer_pos, bytes_read;
	char *line = NULL, *temp = NULL;
	int line_size = 0, new_line_pos, i;

	if (fd < 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= bytes_read)
		{
			bytes_read = read(fd, buffer, READ_SIZE);
			if (bytes_read <= 0)
				return (line_size > 0 ? line : NULL);
			buffer_pos = 0, buffer[bytes_read] = '\0';
		}
		new_line_pos = buffer_pos;
		while (new_line_pos < bytes_read && buffer[new_line_pos] != '\n')
			new_line_pos++;
		temp = realloc(line, line_size + (new_line_pos - buffer_pos) + 1);
		if (!temp)
			return (free(line), NULL);
		line = temp, i = 0;
		while (buffer_pos < new_line_pos)
			line[line_size + i] = buffer[buffer_pos], i++, buffer_pos++;
		line[line_size + i] = '\0', line_size += i;
		if (new_line_pos < bytes_read && buffer[new_line_pos] == '\n')
			return (buffer_pos++, line);
	}
}
