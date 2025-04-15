#include <opencc/opencc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void print_usage(const char *prog_name) {
  fprintf(stderr, "Usage: %s -c <config> [\"<string>\"]\n", prog_name);
  fprintf(stderr, "Example:\n");
  fprintf(stderr, "  %s -c t2s \"繁體中文\"\n", prog_name);
  fprintf(stderr, "  %s -c s2t\n", prog_name);
  fprintf(stderr, "  echo \"繁體中文\" | %s -c t2s\n", prog_name);
}

char *read_stdin() {
  size_t size = 0;
  size_t capacity = BUFFER_SIZE;
  char *buffer = malloc(capacity);
  if (!buffer) {
    fprintf(stderr, "Error: Failed to Memory allocation.\n");
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
        fprintf(stderr, "Error: Failed to Memory reallocation.\n");
        free(buffer);
        return NULL;
      }
      buffer = new_buffer;
    }
  }

  return buffer;
}

int main(int argc, char *argv[]) {
  const char *config = NULL;
  const char *input = NULL;

  if (argc < 3) {
    print_usage(argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "-c") == 0) {
    config = argv[2];
  } else {
    print_usage(argv[0]);
    return 1;
  }

  if (argc > 3) {
    input = argv[3];
  } else {
    input = read_stdin();
    if (!input) {
      fprintf(stderr, "Error: Failed to read stdin.\n");
      return 1;
    }
  }

  char config_path[256];
  snprintf(config_path, sizeof(config_path), "%s.json", config);

  opencc_t od = opencc_open(config_path);
  if (od == (opencc_t)-1) {
    perror("Error: Failed to opencc_open.\n");
    if (argc == 3)
      free((char *)input);
    return 1;
  }

  char *converted = opencc_convert_utf8(od, input, strlen(input));
  if (converted == NULL) {
    perror("Error: Failed to convert input.\n");
    opencc_close(od);
    if (argc == 3)
      free((char *)input);
    return 1;
  }

  printf("%s\n", converted);

  opencc_convert_utf8_free(converted);
  opencc_close(od);
  if (argc == 3)
    free((char *)input);

  return 0;
}
