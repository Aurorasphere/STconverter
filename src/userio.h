#ifndef USERIO_H
#define USERIO_H

#include "aurotype.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *read_file(const char *path, bool force);
bool write_file(const char *path, const char *content);
char *read_stdin();

#endif
