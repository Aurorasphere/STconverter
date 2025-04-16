#include "aurotype.h"
#include "message.h"
#include "userio.h"
#include <opencc/opencc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

i32 main(int argc, char *argv[]) {
  const char *config = NULL;
  const char *input = NULL;
  bool input_from_stdin = false;

  // Handle special flags early
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--cat") == 0) {
      print_cat_easteregg();
      return 0;
    }
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      print_usage(argv[0]);
      return 0;
    }
  }

  // Parse config
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
      config = argv[++i];
    } else if (!input && i > 0 && argv[i][0] != '-') {
      input = argv[i];
    }
  }

  if (!config) {
    print_usage(argv[0]);
    return 1;
  }

  // Read input if not provided
  if (!input) {
    input = read_stdin();
    if (!input) {
      fprintf(stderr, "\033[1;31mError\033[0m: Failed to read input.\n");
      return 1;
    }
    input_from_stdin = true;
  }

  // Prepare OpenCC config path
  char config_path[256];
  snprintf(config_path, sizeof(config_path), "%s.json", config);

  // Run OpenCC
  opencc_t od = opencc_open(config_path);
  if (od == (opencc_t)-1) {
    perror("\033[1;31mError\033[0m: Failed to execute opencc_open");
    if (input_from_stdin)
      free((char *)input);
    return 1;
  }

  char *converted = opencc_convert_utf8(od, input, strlen(input));
  if (!converted) {
    perror("\033[1;31mError\033[0m: Failed to convert input");
    opencc_close(od);
    if (input_from_stdin)
      free((char *)input);
    return 1;
  }

  printf("%s\n", converted);

  opencc_convert_utf8_free(converted);
  opencc_close(od);
  if (input_from_stdin)
    free((char *)input);

  return 0;
}
