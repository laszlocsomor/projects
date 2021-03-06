#include <stdio.h>

#include "fstream/ifstm.h"
#include "fstream/ofstm.h"

struct ifstm_b8 {
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

  struct ifstm_b8 is;
  struct ofstm_b4 os;
  if (ifstm(in, &is.stm, 8) || ofstm(out, &os.stm, 4)) {
    return 1;
  }

  int b = 0;
  while ((b = ifstm_read(&is.stm)) < 256) {
    printf("read: %d\n", b);
    if (ofstm_print(&os.stm, "read: ") || ofstm_write(&os.stm, &b, 1) ||
        ofstm_write(&os.stm, "\n", 1)) {
      return 1;
    }
    uint8_t pk[10];
    for (int i = 0; i < 10 && ifstm_peek(&is.stm, i, pk) == i; i++) {
      printf("  peeked %d:", i);
      if (ofstm_print(&os.stm, "  peeked: ")) {
        return 1;
      }
      for (int j = 0; j < i; ++j) {
        printf(" %d", pk[j]);
      }
      if (ofstm_write(&os.stm, pk, i) || ofstm_print(&os.stm, "\n")) {
        return 1;
      }
      printf("\n");
    }
  }

  return ofstm_flush(&os.stm);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <in_file> <out_file>\n", argv[0]);
    return 1;
  }
  FILE *f, *g;

  f = fopen(argv[1], "rb");
  g = fopen(argv[2], "wb");
  int res = foo(f, g);
  fclose(f);
  fclose(g);

  (void)argc;
  (void)argv;
  return res;
}
