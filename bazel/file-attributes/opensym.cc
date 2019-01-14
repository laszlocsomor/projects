#include <windows.h>
#include <stdio.h>
#include <vector>

int main(void) {
  static constexpr DWORD kAllShare =
      FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;

  for (const wchar_t* path : {
      L"\\\\?\\D:\\src\\tmp\\BUILD",
      L"\\\\?\\D:\\src\\tmp\\examples",
      L"\\\\?\\D:\\src\\tmp\\junc",
      L"\\\\?\\D:\\src\\tmp\\foo.sym",
      L"\\\\?\\D:\\src\\tmp\\foo.dir",
      L"\\\\?\\D:\\src\\tmp\\foo.sym.bad",
      L"\\\\?\\D:\\src\\tmp\\foo.dir.bad",
      L"\\\\?\\D:\\src\\tmp\\junc.dangl",
      L"\\\\?\\D:\\src\\tmp\\file.dangl",
      L"\\\\?\\D:\\src\\tmp\\dir.dangl",
      L"\\\\?\\D:\\src\\tmp\\junc.file",
      }) {
    wprintf(L"%s\n", path);

    HANDLE h = CreateFileW(path, 0, kAllShare, NULL, OPEN_EXISTING,
                           FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (h == INVALID_HANDLE_VALUE) {
      printf("  open1: failed, error: %d\n", GetLastError());
    } else {
      BY_HANDLE_FILE_INFORMATION info;
      GetFileInformationByHandle(h, &info);
      printf("  open1: succeeded, attr: 0x%08x, info.attr: 0x%08x, is_dir: %d\n",
          GetFileAttributesW(path),
          info.dwFileAttributes,
          info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? 1 : 0);
      CloseHandle(h);
    }
          
    h = CreateFileW(path, 0, kAllShare, NULL, OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) {
      printf("  open2: failed, error: %d\n", GetLastError());
    } else {
      BY_HANDLE_FILE_INFORMATION info;
      GetFileInformationByHandle(h, &info);
      printf("  open2: succeeded, attr: 0x%08x, info.attr: 0x%08x, is_dir: %d\n",
          GetFileAttributesW(path),
          info.dwFileAttributes,
          info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? 1 : 0);
      CloseHandle(h);
    }
  }
  return 0;
}
