#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "argc = %d, should be 2\n", argc);
    return 1;
  }
  int delay = 0;
  sscanf(argv[1], "%d", &delay);
  for (int i = 0; i < delay; ++i) {
#if defined(_WIN32)
    Sleep(1000);
#else
    sleep(1);
#endif
    printf("slept %d sec\r", i + 1);
  }
  return 0;
}
