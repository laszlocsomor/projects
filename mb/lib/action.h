#ifndef MB_LIB_ACTION_H_
#define MB_LIB_ACTION_H_ 1

#include "lib/cmd.h"
#include "lib/env.h"
#include "lib/path.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <memory>

namespace mb {

struct Action {
  std::unique_ptr<Path[]> in_;
  std::unique_ptr<Path[]> out_;
  Cmd* cmd_;
  Env* env_;
  Path* cwd_;
};

}  // namespace mb

#endif  // MB_LIB_ACTION_H_
