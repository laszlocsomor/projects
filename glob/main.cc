#include <stdio.h>
#include "tbuf.h"

int main(int argc, char **argv) {
  printf("%d\n", offset_of({2, "xx"}, {4, "abxxcxx"}, 1));
  return 0;
}
