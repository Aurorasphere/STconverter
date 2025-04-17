#include "autodetect.h"

bool detect_is_simplified(const char *text) {
  int simplified_count = 0;
  int traditional_count = 0;

  while (*text) {
    if (strchr(simplified_only_chars, *text)) {
      simplified_count++;
    }
    if (strchr(traditional_only_chars, *text)) {
      traditional_count++;
    }
    text++;
  }

  if (simplified_count == 0 && traditional_count == 0) {
    return true;
  }

  if (simplified_count == traditional_count) {
    fprintf(stderr, "\033[1;31mError\033[0m: Cannot determine text type.\n");
    exit(1);
  }

  return (simplified_count > traditional_count);
}
