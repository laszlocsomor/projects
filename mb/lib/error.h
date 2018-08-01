#ifndef MB_LIB_ERROR_H_
#define MB_LIB_ERROR_H_ 1

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace mb {

struct Error {
  DWORD value;
};

}  // namespace mb

#endif  // MB_LIB_ERROR_H_

