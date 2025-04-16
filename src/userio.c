#include "userio.h"

char *read_file(const char *path) {
  FILE *fp = fopen(path, "r");
  if (!fp)
    return NULL;

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);

  char *buf = malloc(size + 1);
  if (!buf) {
    fclose(fp);
    return NULL;
  }

  fread(buf, 1, size, fp);
  buf[size] = '\0';
  fclose(fp);
  return buf;
}

bool write_file(const char *path, const char *content) {
  FILE *fp = fopen(path, "w");
  if (!fp)
    return false;

  fputs(content, fp);
  fclose(fp);
  return true;
}

char *read_stdin() {
  usize size = 0;
  usize capacity = BUFFER_SIZE;
  char *buffer = malloc(capacity);
  if (!buffer) {
    fprintf(stderr, "\033[1;31mError\033[0m: Failed to allocate memory.\n");
    return NULL;
  }

  size_t len;
  while (fgets(buffer + size, BUFFER_SIZE, stdin)) {
    len = strlen(buffer + size);
    size += len;
    if (buffer[size - 1] == '\n') {
      buffer[size - 1] = '\0';
      break;
    }
    if (size + BUFFER_SIZE > capacity) {
      capacity *= 2;
      char *new_buffer = realloc(buffer, capacity);
      if (!new_buffer) {
        fprintf(stderr,
                "\033[1;31mError\033[0m: Failed to reallocate memory.\n");
        free(buffer);
        return NULL;
      }
      buffer = new_buffer;
    }
  }

  return buffer;
}
