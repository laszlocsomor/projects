#ifndef _OFSTM_H_
#define _OFSTM_H_ 1

#include <stdint.h>
#include <stdio.h>

#include "ofstm_imp.h"

struct ofstm;

// Initializes the output file stream 'out', using the opened-for-write 'f'.
// Returns:
//   0: success
//   1: failure, I/O error
int ofstm(FILE *f, struct ofstm *out);

// Writes 0..'n' bytes from 'p' into the output file stream 's'.
// Returns:
//   0: success
//   1: failure, I/O error
int ofstm_wr(struct ofstm *s, const void *p, size_t n);

// Writes the null-terminated string from 'p' into the output file stream 's'.
// Returns:
//   0: success
//   1: failure, I/O error
int ofstm_pnt(struct ofstm *s, const char *p);

// Writes the bytes currently in the stream's buffer into the file.
//   0: success
//   1: failure, I/O error
int ofstm_fsh(struct ofstm *s);

#endif // _OFSTM_H_
