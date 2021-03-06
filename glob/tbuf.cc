#include "tbuf.h"

#include <limits.h>

size_t offset_of(TBuf substr, TBuf str, size_t offset) {
  if (substr.size_ == 0) {
    // Empty string is a substring of every other string.
    return 0;
  }

  if (str.size_ < substr.size_) {
    // Substring cannot be longer than containing string.
    return SIZE_MAX;
  }

  const uint8_t *p_str = reinterpret_cast<const uint8_t *>(str.p_);
  const uint8_t *p_substr = reinterpret_cast<const uint8_t *>(substr.p_);
  const size_t max_offset = str.size_ + 1 - substr.size_;
  for (size_t start = offset; start < max_offset; ++start) {
    if (p_str[start] == p_substr[0]) {
      bool matches = true;
      for (size_t i = 1; i < substr.size_; ++i) {
        if (p_str[start + i] != p_substr[i]) {
          matches = false;
          break;
        }
      }
      if (matches) {
        return start;
      }
    }
  }
  return SIZE_MAX;
}
