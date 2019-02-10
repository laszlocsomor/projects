#include <stdio.h>

#include "ifstm.h"
#include "ofstm.h"

struct ifstm_p4 {
  struct ifstm stm;
  uint8_t pages[8]; // page_size = 4
};

struct ofstm_b4 {
  struct ofstm stm;
  uint8_t buf[4]; // buf_size = 4
};

int foo(FILE *in, FILE *out) {
  if (!in || !out) {
    return 1;
  }

  struct ifstm_p4 is;
  struct ofstm_b4 os;
  if (ifstm(in, &is.stm, 4) || ofstm(out, &os.stm, 4)) {
    return 1;
  }

  int b = 0;
  while ((b = ifstm_rd(&is.stm)) < 256) {
    printf("read: %d\n", b);
    if (ofstm_pnt(&os.stm, "read: ") || ofstm_wr(&os.stm, &b, 1) ||
        ofstm_wr(&os.stm, "\n", 1)) {
      return 1;
    }
    uint8_t pk[10];
    for (int i = 0; i < 10 && ifstm_pk(&is.stm, i, pk) == i; i++) {
      printf("  peeked %d:", i);
      if (ofstm_pnt(&os.stm, "  peeked: ")) {
        return 1;
      }
      for (int j = 0; j < i; ++j) {
        printf(" %d", pk[j]);
      }
      if (ofstm_wr(&os.stm, pk, i) || ofstm_pnt(&os.stm, "\n")) {
        return 1;
      }
      printf("\n");
    }
  }

  return ofstm_fsh(&os.stm);
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
  return res;
}
