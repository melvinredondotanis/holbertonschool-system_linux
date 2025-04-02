#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * struct content - stores entry information
 * @name:   string buffer
 * @tperm:  permissions buffer
 * @lc:     link count
 * @uid:    user id
 * @gid:    group id
 * @usr:    user name
 * @grp:    group name
 * @siz:    content size in bytes
 * @mtim:   last modified time
 */
typedef struct content
{
	char name[256];
	char tperm[11];
	long lc;
	long uid;
	long gid;
	char *usr;
	char *grp;
	long siz;
	char mtim[12];
} content;

/**
 * struct option - stores options state
 * @_1: to print contents per line
 * @a:  show hidden contents
 * @A:  omit . and ..
 * @l:  show lstat information
 * @r:  sort in reverse
 * @S:  sort by content size
 * @t:  sort by modification time
 * @R:  list subdirectories recursively
 */
typedef struct option
{
	bool _1;
	bool a;
	bool A;
	bool l;
	bool r;
	bool S;
	bool t;
	bool R;
} option;

/* Strings */
void *_memcpy(void *dest, const void *src, size_t n);
size_t _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, const char *src);
char *str_toupper(char *str);

#endif /* HLS_H */