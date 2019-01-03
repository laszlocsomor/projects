#include "a.h"
#include <stdio.h>

int main(int argc, char**) {
  printf("foo(%d)=%d\n", argc, foo(argc));
  return 0;
}
