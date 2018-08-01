#include <stdio.h>

 extern "C" int foo1();

int main(void) {
  printf("foo=%d\n", foo1());
}
