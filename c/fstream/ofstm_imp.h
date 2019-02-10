#ifndef _OFSTM_IMP_H_
#define _OFSTM_IMP_H_ 1

#include <stdint.h>
#include <stdio.h>

struct ofstm {
  FILE *f;
  size_t pos, buf_size;
  uint8_t buf[0];
};

#endif // _OFSTM_IMP_H_
