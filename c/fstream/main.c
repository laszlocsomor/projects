#include <stdio.h>

#include "ifstm.h"
#include "ofstm.h"

int foo(FILE *in, FILE *out) {
  if (!in || !out) {
    return 1;
  }

  struct ifstm is;
  struct ofstm os;
  if (ifstm(in, &is) || ofstm(out, &os)) {
    return 1;
  }

  int b = 0;
  while ((b = ifstm_rd(&is)) < 256) {
    printf("read: %d\n", b);
    if (ofstm_pnt(&os, "read: ") || ofstm_wr(&os, &b, 1) ||
        ofstm_wr(&os, "\n", 1)) {
      return 1;
    }
    uint8_t pk[10];
    for (int i = 0; i < 10 && ifstm_pk(&is, i, pk) == i; i++) {
      printf("  peeked %d:", i);
      if (ofstm_pnt(&os, "  peeked: ")) {
        return 1;
      }
      for (int j = 0; j < i; ++j) {
        printf(" %d", pk[j]);
      }
      if (ofstm_wr(&os, pk, i) || ofstm_pnt(&os, "\n")) {
        return 1;
      }
      printf("\n");
    }
  }

  return ofstm_fsh(&os);
}

int main(int argc, char **argv) {
  FILE *f, *g;

  f = fopen("./hello.txt", "rb");
  g = fopen("./world.txt", "wb");
  int res = foo(f, g);
  fclose(f);
  fclose(g);

  (void)argc;
  (void)argv;
  return 0;
}
