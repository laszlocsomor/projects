#include "lib/executor.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wchar.h>

#include <memory>

namespace mb {

bool ExecuteAction(std::unique_ptr<Action> action, Error* error) {
  static constexpr size_t kMaxCmdline = 0x8000;

  std::unique_ptr<WCHAR[]> cmdline(new WCHAR[kMaxCmdline]);
  wcsncpy(cmdline.get(), action.cmd.Get(), kMaxCmdline);
  if (cmdline.get()[kMaxCmdline - 1]) {
    // wcsncpy fills the destination buffer with zeroes unless the source is
    // longer than the allowed size. In this case, the command is too long.
    // TODO: Figure out how to report errors as strings, while also supporting
    // reporting GetLastError()-returned errors, then report the error here.
    return false;
  }

  PROCESS_INFORMATION processInfo;
  STARTUPINFOW startupInfo = {0};
  BOOL ok = CreateProcessW(
      NULL, cmdline.get(), NULL, NULL, FALSE, CREATE_NO_WINDOW, env_->Get(),
      cwd_->Get(), &startupInfo, &processInfo);
  if (!ok) {
    DWORD err = GetLastError();
    // TODO: Figure out how to report errors as strings, while also supporting
    // reporting GetLastError()-returned errors, then report the error here.
    return false;
  }

  WaitForSingleObject(processInfo.hProcess, INFINITE);
  DWORD exit;
  BOOL success = GetExitCodeProcess(processInfo.hProcess, &exit);
  if (!success) {
    DWORD err = GetLastError();
    if (error != nullptr) {
      error->value = err;
    }
  }
  CloseHandle(processInfo.hProcess);
  CloseHandle(processInfo.hThread);
  return success != FALSE;
}

}  // namespace mb
