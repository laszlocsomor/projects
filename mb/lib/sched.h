#ifndef MB_LIB_SCHED_H_
#define MB_LIB_SCHED_H_ 1

#include "lib/action.h"

namespace mb {

// Decides which action is ready to be executed.
class Scheduler {
 public:
  void Enque(std::unique_ptr<Action> action);
  std::unique_ptr<Action> Next();
};

}  // namespace mb

#endif  // MB_LIB_SCHED_H_


