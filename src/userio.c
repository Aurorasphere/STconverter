#include "userio.h"

char *read_file(const char *path, bool force) {
  FILE *fp = fopen(path, "rb");
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
  fclose(fp);
  buf[size] = '\0';

  for (long i = 0; i < size; i++) {
    if (buf[i] == '\0') {
      if (force) {
        fprintf(stderr, "\033[1;33mWarning\033[0m: Input file seems to be "
                        "non-text file, but continuing due to --force.\n");
        break;
      } else {
        fprintf(stderr, "\033[1;31mError\033[0m: Input file seems to be a "
                        "non-text file.\n");
        free(buf);
        return NULL;
      }
    }
  }

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
