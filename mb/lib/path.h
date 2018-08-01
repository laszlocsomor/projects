#ifndef MB_LIB_PATH_H_
#define MB_LIB_PATH_H_ 1

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <memory>

namespace mb {

struct Path {
  std::unique_ptr<WCHAR[]> value;

  const WCHAR* Get() const;
};

}  // namespace mb

#endif  // MB_LIB_PATH_H_


