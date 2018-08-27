#include <windows.h>
#include <stdio.h>

typedef WINBASEAPI BOOL (*WINAPI LPCompareObjectHandles)(
    _In_ HANDLE hFirstObjectHandle,
    _In_ HANDLE hSecondObjectHandle
    );

int wmain(int argc, wchar_t** argv) {
  if (argc != 3) {
    fwprintf(stderr, L"Usage: %s <path1> <path2>\n", argv[0]);
    return 1;
  }

  HMODULE dll = LoadLibraryA("kernelbase.dll");
  if (dll == NULL) {
    DWORD err = GetLastError();
    fwprintf(stderr, L"LoadLibraryA failed: error %d\n", err);
    return 1;
  }

  // Load CompareObjectHandles dynamically. The Windows SDK does not contain
  // kernelbase.lib so we cannot link to it at link-time.
  LPCompareObjectHandles compare_handles =
      reinterpret_cast<LPCompareObjectHandles>(
          GetProcAddress(dll, "CompareObjectHandles"));

  if (compare_handles == nullptr) {
    DWORD err = GetLastError();
    fwprintf(stderr, L"GetProcAddress failed: error %d\n", err);
    return 1;
  }

  HANDLE h[2];
  for (int i = 0; i < 2; ++i) {
    // Try opening the path as a file.
    h[i] = CreateFileW(
        argv[i + 1], 0, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h[i] == INVALID_HANDLE_VALUE) {
      // Try opening the path as a directory.
      h[i] = CreateFileW(
          argv[i + 1], 0,
          FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
          NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
      if (h[i] == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        fwprintf(stderr, L"Failed to open \"%s\": error %d\n", argv[i + 1], err);
        if (i > 0) {
          CloseHandle(h[0]);
        }
        return 1;
      }
    }
  }

  SetLastError(0);
  BOOL result = compare_handles(h[0], h[1]);
  DWORD err = GetLastError();
  wprintf(L"According to CompareObjectHandles, the handles are %s. Error: %d\n",
      result == FALSE ? L"NOT equal" : L"equal", err);

  for (int i = 0; i < 2; i++) {
    static constexpr size_t kSize = 0x8000;
    WCHAR path[kSize];
    DWORD len = GetFinalPathNameByHandleW(h[i], path, kSize, VOLUME_NAME_DOS);
    if (len >= kSize) {
      fwprintf(stderr, L"final path of arg %d is too long\n", i + 1);
      return 1;
    } else if (len == 0) {
      DWORD err = GetLastError();
      fwprintf(stderr, L"GetFinalPathNameByHandleW(%s) failed, error %d\n", argv[i + 1], err);
      return 1;
    }
    wprintf(L"path%d (real) = \"%s\"\n", i + 1, path);
  }

  CloseHandle(h[0]);
  CloseHandle(h[1]);
  return 0;
}
