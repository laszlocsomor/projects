#include <stdio.h>

extern "C" int foo(int);

int main(int argc, char**) {
  printf("hello from main!\n foo=%d\n", foo(argc));
  return 0;
}
