#ifndef MB_LIB_EXECUTOR_H_
#define MB_LIB_EXECUTOR_H_ 1

#include "lib/error.h"
#include "lib/sched.h"

namespace mb {

// 
class Executor {
 public:
  // Starts executing Actions that `sched` returns.
  bool Start(Scheduler* sched, Error* error = nullptr);

  // Blocks until all Actions in the scheduler are executed.
  bool Finish(Error* error = nullptr);

  // bool Execute(std::unique_ptr<Action> action, Error* error = nullptr);
};

}  // namespace mb

#endif  // MB_LIB_EXECUTOR_H_

