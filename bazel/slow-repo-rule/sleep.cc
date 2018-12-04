#if defined(_WIN32)
#include <windows.h>
#include <stdio.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "argc = %d, should be 3\nUsage: $0 <sleep-sec> <output-file>\n", argc);
    return 1;
  }

  FILE* f = fopen(argv[2], "at");
  fseek(f, 0, SEEK_END);
  fprintf(f, "start\n");
  fclose(f);

  int delay = 0;
  sscanf(argv[1], "%d", &delay);
  for (int i = 0; i < delay; ++i) {
#if defined(_WIN32)
    Sleep(1000);
#else
    sleep(1);
#endif
    FILE* f = fopen(argv[2], "at");
    fseek(f, 0, SEEK_END);
    fprintf(f, "%d\n", i + 1);
    fclose(f);
    printf("slept %d sec\r", i + 1);
  }
  return 0;
}
