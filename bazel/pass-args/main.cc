#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include <functional>
#include <memory>
#include <string>
#include <vector>

class Defer {
 public:
  explicit Defer(std::function<void()> f) : f_(f) {}
  ~Defer() { f_(); }

 private:
  std::function<void()> f_;
};

void LogError(const int line, const wchar_t* msg) {
#define _WSTR_HELPER_1(x) L##x
#define _WSTR_HELPER_2(x) _WSTR_HELPER_1(x)
  wprintf(L"ERROR(" _WSTR_HELPER_2(__FILE__) L":%d) %s\n", line, msg);
#undef _WSTR_HELPER_2
#undef _WSTR_HELPER_1
}

void LogInfo(const int line, const wchar_t* msg) {
#define _WSTR_HELPER_1(x) L##x
#define _WSTR_HELPER_2(x) _WSTR_HELPER_1(x)
  wprintf(L"INFO(" _WSTR_HELPER_2(__FILE__) L":%d) %s\n", line, msg);
#undef _WSTR_HELPER_2
#undef _WSTR_HELPER_1
}

void LogErrorWithValue(const int line, const char* msg, DWORD error_code) {
  printf("ERROR(" __FILE__ ":%d) error code: %d (0x%08x): %s\n", line,
         error_code, error_code, msg);
}

bool AddCommandLineArg(
    const wchar_t* arg, const size_t arg_size, const bool first,
    wchar_t* cmdline, const size_t cmdline_limit,
    size_t* inout_cmdline_len) {
  LogInfo(__LINE__,
          (std::wstring(L"AddCommandLineArg(") + arg + L")").c_str());

  if (arg_size == 0) {
    const size_t len = (first ? 0 : 1) + 2;
    if (*inout_cmdline_len + len >= cmdline_limit) {
      LogError(__LINE__,
               (std::wstring(L"Failed to add command line argument \"") +
                   arg + L"\"; command would be too long").c_str());
      return false;
    }

    size_t offset = *inout_cmdline_len;
    if (!first) {
      cmdline[offset] = L' ';
      offset += 1;
    }
    cmdline[offset] = L'"';
    cmdline[offset + 1] = L'"';
    *inout_cmdline_len += len;
    return true;
  } else {
    const size_t len = (first ? 0 : 1) + arg_size;
    if (*inout_cmdline_len + len >= cmdline_limit) {
      LogError(__LINE__,
               (std::wstring(L"Failed to add command line argument \"") +
                   arg + L"\"; command would be too long").c_str());
      return false;
    }

    size_t offset = *inout_cmdline_len;
    if (!first) {
      cmdline[offset] = L' ';
      offset += 1;
    }
    wcsncpy(cmdline + offset, arg, arg_size);
    offset += arg_size;
    *inout_cmdline_len += len;
    return true;
  }
}

bool CreateCommandLine(
    const std::wstring& path, const std::vector<std::wstring>& args,
    std::unique_ptr<WCHAR[]>* result) {
  // kMaxCmdline value: see lpCommandLine parameter of CreateProcessW.
  static constexpr size_t kMaxCmdline = 32767;

  // Add an extra character for the final null-terminator.
  result->reset(new WCHAR[kMaxCmdline + 1]);

  size_t total_len = 0;
  if (!AddCommandLineArg(path.c_str(), path.size(), true,
                         result->get(), kMaxCmdline, &total_len)) {
    return false;
  }

  for (const auto& arg : args) {
    if (!AddCommandLineArg(arg.c_str(), arg.size(), false, result->get(),
                           kMaxCmdline, &total_len)) {
      return false;
    }
  }
  // Add final null-terminator. There's surely enough room for it:
  // AddCommandLineArg kept validating that we stay under the limit of
  // kMaxCmdline, and the buffer is one WCHAR larger than that.
  result->get()[total_len] = 0;
  return true;
}

bool StartSubprocess(const std::wstring& path,
                     const std::vector<std::wstring>& args, HANDLE* process) {
  std::unique_ptr<WCHAR[]> cmdline;
  if (!CreateCommandLine(path, args, &cmdline)) {
    return false;
  }
  PROCESS_INFORMATION processInfo;
  STARTUPINFOW startupInfo = {0};

  LogInfo(__LINE__,
          (std::wstring(L"cmdline for CreateProcessW: {") + cmdline.get() +
                        L"}").c_str());
  if (CreateProcessW(NULL, cmdline.get(), NULL, NULL, FALSE,
                     CREATE_UNICODE_ENVIRONMENT, NULL, NULL, &startupInfo,
                     &processInfo) != 0) {
    CloseHandle(processInfo.hThread);
    *process = processInfo.hProcess;
    return true;
  } else {
    DWORD err = GetLastError();
    LogErrorWithValue(__LINE__, "CreateProcessW failed", err);
    return false;
  }
}

int WaitForSubprocess(HANDLE process) {
  DWORD result = WaitForSingleObject(process, INFINITE);
  switch (result) {
    case WAIT_OBJECT_0: {
      DWORD exit_code;
      if (!GetExitCodeProcess(process, &exit_code)) {
        DWORD err = GetLastError();
        LogErrorWithValue(__LINE__, "GetExitCodeProcess failed", err);
        return 1;
      }
      return exit_code;
    }
    case WAIT_FAILED: {
      DWORD err = GetLastError();
      LogErrorWithValue(__LINE__, "WaitForSingleObject failed", err);
      return 1;
    }
    default:
      LogErrorWithValue(
          __LINE__, "WaitForSingleObject returned unexpected result", result);
      return 1;
  }
}

int RunSubprocess(const std::wstring& test_path,
                  const std::vector<std::wstring>& args) {
  HANDLE process;
  if (!StartSubprocess(test_path, args, &process)) {
    return 1;
  }
  Defer close_process([process]() { CloseHandle(process); });

  return WaitForSubprocess(process);
}

int wmain(int argc, wchar_t** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: $0 <program>\n");
    return 1;
  }
  std::vector<std::wstring> args = {
    L"foo",
    L"a b",
    L"\"a b\"",
    L"",
    L"\"\"",
    L"bar",
    L"\"baz\"",
    L"last",
  };

  return RunSubprocess(argv[1], args);
}
