#ifndef _IFSTM_H_
#define _IFSTM_H_ 1

#include <stdint.h>
#include <stdio.h>

#include "ifstm_imp.h"

struct ifstm;

// Initializes the input file stream 's', using the opened-for-read 'f'.
// 's' should have 2 * 'page_size' many bytes allocated in 'ifstm::pages'.
// Returns:
//   0: success
//   1: failure, I/O error
int ifstm(FILE *f, struct ifstm *s, size_t page_size);

// Reads one byte from the stream, and moves the cursor ahead.
// Returns:
//   0..255: success, the value of the read byte
//   256 (IFSTM_READ_EOF): failure, EOF was reached
//   257 (IFSTM_READ_IO): failure, I/O error
int ifstm_read(struct ifstm *s);

// Peeks at 'n' bytes starting at the current cursor.
// Writes into 'out' the 0..'n' successfully peeked bytes.
// Returns:
//   0..n: the number of successfully peeked bytes
size_t ifstm_peek(struct ifstm *s, size_t n, void *out);

#endif // _IFSTM_H_
