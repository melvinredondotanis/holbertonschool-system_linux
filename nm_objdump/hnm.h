#ifndef HNM_H
#define HNM_H

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define USAGE "Usage: hnm [objfile ...]\n"

int displays_symbols(char *filename, char *program_name);

#endif /* HNM_H */
