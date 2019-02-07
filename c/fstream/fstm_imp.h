#ifndef _FSTM_IMP_H_
#define _FSTM_IMP_H_ 1

#include <stdio.h>
#include <stdint.h>

#ifdef _IFSTM_PAGE 
#error "_IFSTM_PAGE already defined"
#else
// Size of the input file stream's page size, in bytes.
// The stream's buffer holds two pages of data.
#define _IFSTM_PAGE 1024
#endif

#ifdef IFSTM_RD_EOF
#error "IFSTM_RD_EOF already defined"
#else
// Return value of ifstm_rd: failed to read due to EOF reached.
#define IFSTM_RD_EOF 256
#endif

#ifdef IFSTM_RD_IO
#error "IFSTM_RD_IO already defined"
#else
// Return value of ifstm_rd: failed to read due to I/O error.
#define IFSTM_RD_IO 257
#endif

struct fstm {
  FILE* f;
  size_t pos, end;
  size_t p1size, p2size;
  uint8_t pages[_IFSTM_PAGE * 2];
};

#endif  // _FSTM_IMP_H_
