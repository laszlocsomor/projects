#include <stdio.h>

extern "C" {
  __declspec(dllimport) int bar(int x);
}

int main(int argc, char** argv) {
  printf("argc=%d, bar(%d)=%d\n", argc, argc, bar(argc));
  return 0;
}
