#include <windows.h>
#include <stdio.h>
int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "argc = %d, should be 2\n", argc);
    return 1;
  }
  int delay = 0;
  sscanf(argv[1], "%d", &delay);
  for (int i = 0; i < delay; ++i) {
    Sleep(1000);
    printf("slept %d sec\r", i + 1);
  }
  return 0;
}
