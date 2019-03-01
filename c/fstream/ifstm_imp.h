#ifndef _IFSTM_IMP_H_
#define _IFSTM_IMP_H_ 1

#include <stdint.h>
#include <stdio.h>

#ifdef IFSTM_READ_EOF
#error "IFSTM_READ_EOF already defined"
#else
// Return value of ifstm_read: failed to read due to EOF reached.
#define IFSTM_READ_EOF 256
#endif

#ifdef IFSTM_READ_IO
#error "IFSTM_READ_IO already defined"
#else
// Return value of ifstm_read: failed to read due to I/O error.
#define IFSTM_READ_IO 257
#endif

struct ifstm {
  FILE *f;
  size_t pos, end;
  size_t next_size; // size of the inactive page
  size_t page_size;
  uint8_t pages[0];
};

#endif // _IFSTM_IMP_H_
