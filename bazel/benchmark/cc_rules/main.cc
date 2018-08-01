#include <stdio.h>

#define _C(a,b) a##b
#define C(a,b) _C(a,b)

extern "C" int C(foo, ROOTVALUE)(void);

int main(void) {
  printf("foo=%d\n", C(foo, ROOTVALUE)());
}
