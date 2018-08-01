#include "lib/path.h"

namespace mb {

const WCHAR* Path::Get() const {
  if (value == nullptr) {
    return L"";
  } else {
    return value.get();
  }
}

}  // namespace mb
