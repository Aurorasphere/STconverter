#include "aurotype.h"
#include "autodetect.h"
#include "message.h"
#include "userio.h"
#include <opencc/opencc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

i32 main(int argc, char *argv[]) {
  const char *config = NULL;
  const char *input_path = NULL;
  const char *output_path = NULL;
  const char *input = NULL;
  bool input_allocated = false;
  bool input_direct = false;
  bool autodetect = false;
  bool force = false;

  // Handle special flags first
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--cat") == 0) {
      print_cat_easteregg();
      return 0;
    }
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      print_help(argv[0]);
      return 0;
    }
    if (strcmp(argv[i], "--auto") == 0 || strcmp(argv[i], "-A") == 0) {
      autodetect = true;
    }
    if (strcmp(argv[i], "--force") == 0 || strcmp(argv[i], "-f") == 0) {
      force = true;
    }

    if (strcmp(argv[i], "--list-configs") == 0) {
      print_list_config();
      return 0;
    }
  }

  // Parse other options
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
      config = argv[++i];
    } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
      input_path = argv[++i];
    } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
      output_path = argv[++i];
    } else if (argv[i][0] != '-') {
      input = argv[i];
      input_direct = true;
    }
  }

  if (!config && !autodetect) {
    print_usage(argv[0]);
    return 1;
  }

  // Read input
  if (input_path) {
    input = read_file(input_path, force);
    if (!input) {
      fprintf(stderr, "\033[1;31mError\033[0m: Failed to read input file.\n");
      return 1;
    }
    input_allocated = true;
  } else if (!input_direct) {
    input = read_stdin();
    if (!input) {
      fprintf(stderr, "\033[1;31mError\033[0m: Failed to read from stdin.\n");
      return 1;
    }
    input_allocated = true;
  }
  // Auto detection
  if (autodetect) {
    if (detect_is_simplified(input)) {
      config = "s2t"; // Simplified → Traditional
    } else {
      config = "t2s"; // Traditional → Simplified
    }
  }

  // Prepare OpenCC config path
  char config_path[256];
  snprintf(config_path, sizeof(config_path), "%s.json", config);

  // Open OpenCC
  opencc_t od = opencc_open(config_path);
  if (od == (opencc_t)-1) {
    perror("\033[1;31mError\033[0m: Failed to execute opencc_open");
    if (input_allocated)
      free((char *)input);
    return 1;
  }

  // Convert input
  char *converted = opencc_convert_utf8(od, input, strlen(input));
  if (!converted) {
    perror("\033[1;31mError\033[0m: Failed to convert input");
    opencc_close(od);
    if (input_allocated)
      free((char *)input);
    return 1;
  }

  // Output result
  if (output_path) {
    if (!write_file(output_path, converted)) {
      fprintf(stderr,
              "\033[1;31mError\033[0m: Failed to write to output file '%s'.\n",
              output_path);
      opencc_convert_utf8_free(converted);
      opencc_close(od);
      if (input_allocated)
        free((char *)input);
      return 1;
    }
  } else {
    printf("%s\n", converted);
  }

  // Cleanup
  opencc_convert_utf8_free(converted);
  opencc_close(od);
  if (input_allocated)
    free((char *)input);

  return 0;
}
