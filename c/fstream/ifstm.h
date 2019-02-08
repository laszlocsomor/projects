#ifndef _IFSTM_H_
#define _IFSTM_H_ 1

#include <stdio.h>
#include <stdint.h>

#include "ifstm_imp.h"

struct ifstm;

// Initializes the input file stream 'out', using the opened-for-read 'f'.
// Returns:
//   0: success
//   1: failure, I/O error
int ifstm(FILE* f, struct ifstm* out);

// Reads one byte from the stream, and moves the cursor ahead.
// Returns:
//   0..255: success, the value of the read byte
//   256 (IFSTM_RD_EOF): failure, EOF was reached
//   257 (IFSTM_RD_IO): failure, I/O error
int ifstm_rd(struct ifstm* s);

// Peeks at 'n' bytes starting at the current cursor.
// Writes into 'out' the 0..'n' successfully peeked bytes.
// Returns:
//   0..n: the number of successfully peeked bytes
size_t ifstm_pk(struct ifstm* s, size_t n, uint8_t* out);

#endif  // _IFSTM_H_
