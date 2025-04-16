#include "message.h"

void print_help(const char *prog) {
  printf("\033[1m%s\033[0m - OpenCC based CLI Chinese character converter.\n\n",
         prog);
  printf("\033[1mOptions\033[0m\n");
  printf("  -i              Read input from file.\n");
  printf("  -o              Write output to file.\n\n");

  printf("  -c              Use specific config.\n");
  printf("  --auto          Automatically detect input as Simplified or "
         "Traditional Chinese.\n");
  printf("  --list-config   List avaliable config settings.\n\n");

  printf("  -h, --help      Print this help message.");
  printf("  -V, --version   Print version.\n");
}

void print_list_config() {
  printf("\033[1mConversion-Related configs:\033[0m");
}

void print_usage(const char *prog_name) {
  fprintf(stderr, "Usage: %s -c <config> [\"<string>\"]\n", prog_name);
  fprintf(stderr, "Example:\n");
  fprintf(stderr, "  %s -c t2s \"繁體中文\"\n", prog_name);
  fprintf(stderr, "  %s -c s2t\n", prog_name);
  fprintf(stderr, "  echo \"繁體中文\" | %s -c t2s\n", prog_name);
}

void print_cat_easteregg() {
  printf("    ／l、\n");
  printf("  （ﾟ､ ｡ ７\n");
  printf("    l  ~ヽ\n");
  printf("    じしf_,)ノ\n\n");

  printf("<3 from \033[1mAurorasphere\033[0m\n");
}
