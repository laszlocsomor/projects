#include <stdio.h>

#include "fstm.h"

int main(int argc, char** argv) {
  FILE* f;
  struct fstm s;

  f = fopen("./hello.txt", "rb");
  if (!f) {
    return 1;
  }

  if (ifstm(f, &s)) {
    fclose(f);
    return 1;
  }

  int b = 0;
  while ((b = ifstm_rd(&s)) < 256) {
    printf("read: %d\n", b);
    uint8_t pk[10];
    for (int i = 0; i < 10 && ifstm_pk(&s, i, pk) == i; i++) {
      printf("  peeked %2d:", i);
      for (int j = 0; j < i; ++j) {
        printf(" %d", pk[j]);
      }
      printf("\n");
    }
  }
  ifstm_close(&s);

  (void) argc;
  (void) argv;
  return 0;
}
