#include <iostream>
#include "generated.h"

static const int FOO = 42;

int main(int argc, char** argv) {
  std::cout << "hello cmake" << FOO << std::endl;
  std::cout << MyMakeVar << std::endl;
  return 0;
}
