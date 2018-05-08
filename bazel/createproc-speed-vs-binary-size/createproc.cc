#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int wmain(int argc, WCHAR** argv) {
  if (argc != 2) {
    printf("ERROR: missing arg\n");
    return 1;
  }

  PROCESS_INFORMATION processInfo;
  STARTUPINFOW startupInfo = {0};
  WCHAR cmdline[MAX_PATH];
  size_t argv0len = wcslen(argv[1]);
  wcscpy(cmdline, argv[1]);
  LARGE_INTEGER t1, t2;
  QueryPerformanceCounter(&t1);
  BOOL ok = CreateProcessW(
      NULL, cmdline, NULL, NULL, FALSE,
      DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP | CREATE_NO_WINDOW, NULL,
      NULL, &startupInfo, &processInfo);
  QueryPerformanceCounter(&t2);
  if (!ok) {
    DWORD err = GetLastError();
    fprintf(stderr, "ERROR: CreateProcessW error: %d\n", err);
    return 1;
  }
  WaitForSingleObject(processInfo.hProcess, INFINITE);
  CloseHandle(processInfo.hProcess);
  CloseHandle(processInfo.hThread);

  LARGE_INTEGER duration, frequency;
  duration.QuadPart = t2.QuadPart - t1.QuadPart;
  QueryPerformanceFrequency(&frequency);
  uint64_t remainder = duration.QuadPart % frequency.QuadPart;
  uint64_t duration_us = (duration.QuadPart / frequency.QuadPart) * 1e6 +
      (remainder * 1e6 / frequency.QuadPart);

  printf(
      "CreateProcess took %I64d us (duration=%I64d ticks, freq=%I64d ticks/sec)\n",
      duration_us, duration.QuadPart, frequency.QuadPart);
  return 0;
}
