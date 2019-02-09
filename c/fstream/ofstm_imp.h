#ifndef _OFSTM_IMP_H_
#define _OFSTM_IMP_H_ 1

#include <stdint.h>
#include <stdio.h>

#ifdef _OFSTM_BUF
#error "_OFSTM_BUF already defined"
#else
// Size of the input file stream's page size, in bytes.
// The stream's buffer holds two pages of data.
#define _OFSTM_BUF 4
#endif

struct ofstm {
  FILE *f;
  size_t pos;
  uint8_t buf[_OFSTM_BUF];
};

#endif // _OFSTM_IMP_H_
