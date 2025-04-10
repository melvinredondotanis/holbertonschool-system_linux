#ifndef _GETLINE_H
#define _GETLINE_H

#define READ_SIZE 102

/**
 * struct fd_buffer - structure to hold file descriptor and buffer
 * @fd: file descriptor
 * @buffer: buffer to hold data
 * @buffer_pos: current position in the buffer
 * @bytes_read: number of bytes read from the file descriptor
 * @next: pointer to the next buffer in the linked list
 */
typedef struct fd_buffer
{
	int fd;
	char buffer[READ_SIZE + 1];
	int buffer_pos;
	int bytes_read;
	struct fd_buffer *next;
} fd_buffer_t;

char *_getline(const int fd);

#endif /* _GETLINE_H */
