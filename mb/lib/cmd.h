#ifndef MB_LIB_CMD_H_
#define MB_LIB_CMD_H_ 1

#include "lib/path.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <memory>

namespace mb {

struct ExitCode {
  DWORD value;
};

struct Cmd {
  std::unique_ptr<WCHAR[]> value;

  inline const WCHAR* Get() const { return value.get(); }
};

}  // namespace mb

#endif  // MB_LIB_CMD_H_
