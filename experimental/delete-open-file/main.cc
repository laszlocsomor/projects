#include <windows.h>
#include <stdio.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: $0 <path-to-delete>\n");
    return 1;
  }

  HANDLE h = CreateFileA(
      argv[1], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
      NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (h == INVALID_HANDLE_VALUE) {
    printf("cannot open \"%s\"\n", argv[1]);
    return 1;
  }
  if (!DeleteFileA(argv[1])) {
    printf("cannot delete \"%s\"\n", argv[1]);
    return 1;
  }
  printf("successfully deleted \"%s\"\n", argv[1]);

  // Get attributes via GetFileAttributesA: returns INVALID_FILE_ATTRIBUTES.
  DWORD attr = GetFileAttributesA(argv[1]);
  printf("attributes: 0x%08x\n", attr);

  // Get attributes via FindFirstFile: can retrieve the attributes.
  WIN32_FIND_DATAA find;
  HANDLE h2 = FindFirstFileA(argv[1], &find);
  if (h2 != INVALID_HANDLE_VALUE) {
    printf("attributes(find): 0x%08x\n", find.dwFileAttributes);
    FindClose(h2);
  }

  // Read from the file.
  DWORD data, read;
  BOOL succ = ReadFile(h, &data, 4, &read, NULL);
  if (succ != FALSE) {
    printf("ReadFile: read %d bytes from deleted file [%c, %c, %c, %c]\n",
        read, data & 0xff, (data >> 8) & 0xff, (data >> 16) & 0xff, (data >> 24) & 0xff);
  } else {
    printf("ReadFile: could not read from deleted file\n");
  }

  // Attempt to re-create the file.
  h2 = CreateFileA(
      argv[1], GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
      NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (h2 != INVALID_HANDLE_VALUE) {
    DWORD written;
    if (WriteFile(h2, "hello\n", 6, &written, NULL)) {
      printf("WriteFile: wrote to deleted-but-recreated file\n");
    } else {
      printf("WriteFile: failed to write to deleted-but-recreated file: %d\n",
             GetLastError());
    }
  } else {
    printf("cannot re-open deleted file: %d\n", GetLastError());
  }
  
  printf("press any key to continue . . .\n");
  ReadFile(GetStdHandle(STD_INPUT_HANDLE), &data, 1, &read, NULL);
  CloseHandle(h);
  return 0;
}
