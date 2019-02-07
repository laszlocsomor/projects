#ifndef _FSTM_H_
#define _FSTM_H_ 1

#include <stdio.h>
#include <stdint.h>

#include "fstm_imp.h"

struct fstm;

// Initializes the input file stream 'out', using the opened-for-read 'f'.
// Returns:
//   0: success
//   1: failure, I/O error
int ifstm(FILE* f, struct fstm* out);

// Reads one byte from the stream, and moves the cursor ahead.
// Returns:
//   0..255: success, the value of the read byte
//   256 (IFSTM_RD_EOF): failure, EOF was reached
//   257 (IFSTM_RD_IO): failure, I/O error
int ifstm_rd(struct fstm* s);

// Peeks at 'n' bytes starting at the current cursor.
// Writes into 'out' the 0..'n' successfully peeked bytes.
// Returns:
//   0..n: the number of successfully peeked bytes
size_t ifstm_pk(struct fstm* s, size_t n, uint8_t* out);

// Returns nonzero if 's' reached EOF.
int ifstm_eof(struct fstm* s);

void ifstm_close(struct fstm* s);

#endif  // _FSTM_H_
