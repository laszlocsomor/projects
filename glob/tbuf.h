#ifndef TBUF_H_
#define TBUF_H_ 1

#include <stdint.h>

typedef struct _TBuf {
  const size_t size_;
  const void *p_;
} TBuf;

// Finds first occurrence of `substr` in `str`, starting search at `offset`.
// Returns the offset if found, returns SIZE_MAX otherwise.
size_t offset_of(TBuf substr, TBuf str, size_t offset = 0);

#endif // TBUF_H_ 1
