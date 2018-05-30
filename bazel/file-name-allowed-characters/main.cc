#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

  SetLastError(0);
  if (!CreateDirectoryW(L"\\\\?\\C:\\tmp", NULL) &&
      GetLastError() != ERROR_ALREADY_EXISTS) {
    fprintf(stderr, "ERROR: cannot create c:\\tmp\n");
    return 1;
  }

  SetLastError(0);
  if (!CreateDirectoryW(L"\\\\?\\C:\\tmp\\names", NULL) &&
      GetLastError() != ERROR_ALREADY_EXISTS) {
    fprintf(stderr, "ERROR: cannot create c:\\tmp\\names\n");
    return 1;
  }

  WCHAR name[] = L"\\\\?\\C:\\tmp\\names\\a&b.txt";
  
  for (int x = 0; x <= 255; ++x) {
    name[18] = x;
    HANDLE h = CreateFileW(
      name,
      GENERIC_WRITE,
      FILE_SHARE_READ,
      NULL,
      CREATE_ALWAYS,
      FILE_ATTRIBUTE_NORMAL,
      NULL);
    if (h == INVALID_HANDLE_VALUE) {
      DWORD err = GetLastError();
      if (x < 32) {
        fprintf(stderr, "%d is illegal (error: %d)\n", x, err);
      } else {
        fprintf(stderr, "%d (%c) is illegal (error: %d)\n", x, x, err);
      }
    } else {
      DWORD w;
      if (!WriteFile(h, "hello\n", 6, &w, NULL)) {
        DWORD err = GetLastError();
        fprintf(stderr, "%d WriteFile failed: %d\n", x, name, err);
      }
      CloseHandle(h);
    }
  }
  return 0;
}
