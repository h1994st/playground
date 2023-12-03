#include "example/bar/bar_utils.h"
#include "foo_utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    printf("%s\n", argv[1]);
  }
  foo_print_time();
  bar_print_num(argc);

  return 0;
}
