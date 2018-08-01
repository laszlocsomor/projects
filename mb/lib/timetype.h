#ifndef MB_LIB_TIMETYPE_H_
#define MB_LIB_TIMETYPE_H_ 1

#include <stdint.h>

namespace mb {

struct Ticks {
  uint64_t value;
};

struct Millis {
  uint64_t value;
};

}  // namespace mb

#endif  // MB_LIB_TIMETYPE_H_

