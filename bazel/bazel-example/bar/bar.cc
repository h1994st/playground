#include <iostream>

#include "bar_utils.h"

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cout << argv[1] << ' ' << argv[2] << std::endl;
  }
  bar_print_num(argc);

  return 0;
}
