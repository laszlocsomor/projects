#ifndef _IFSTM_IMP_H_
#define _IFSTM_IMP_H_ 1

#include <stdint.h>
#include <stdio.h>

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

struct ifstm {
  FILE *f;
  size_t pos, end;
  size_t next_size; // size of the inactive page
  size_t page_size;
  uint8_t pages[0];
};

#endif // _IFSTM_IMP_H_
