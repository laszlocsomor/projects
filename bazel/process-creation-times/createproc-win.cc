#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <iostream>

bool RunProc(char* cmdline, LARGE_INTEGER* create_time, LARGE_INTEGER* full_time) {
  LARGE_INTEGER start;
  QueryPerformanceCounter(&start);
  PROCESS_INFORMATION processInfo;
  STARTUPINFOA startupInfo = {0};
  BOOL ok = CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL,
                           &startupInfo, &processInfo);
  if (!ok) {
    DWORD err = GetLastError();
    std::cerr << "ERROR: CreateProcessA error: " << err << std::endl;
    return false;
  }
  QueryPerformanceCounter(create_time);
  WaitForSingleObject(processInfo.hProcess, INFINITE);
  CloseHandle(processInfo.hProcess);
  CloseHandle(processInfo.hThread);
  QueryPerformanceCounter(full_time);
  create_time->QuadPart -= start.QuadPart;
  full_time->QuadPart -= start.QuadPart;
  return true;
}

size_t percentile_index(size_t total, size_t a, size_t b) {
  return std::min<size_t>(total - 1, (total * a) / b);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    static const size_t kSamples = 1000;
    char cmdline[1000];
    size_t argv0len = strlen(argv[0]);
    strcpy(cmdline, argv[0]);
    cmdline[argv0len] = ' ';
    cmdline[argv0len + 1] = 'x';
    cmdline[argv0len + 2] = 0;
    std::array<LARGE_INTEGER, kSamples> create_time;
    std::array<LARGE_INTEGER, kSamples> full_time;
    for (size_t i = 0; i < kSamples; ++i) {
      if (!RunProc(cmdline, &create_time[i], &full_time[i])) {
        return 1;
      }
      if (i % 10 == 0) {
        std::cout << "ran " << i << " processes\r";
      }
    }
    std::sort(
      create_time.begin(), create_time.end(),
      [](LARGE_INTEGER a, LARGE_INTEGER b) { return a.QuadPart < b.QuadPart; });
    std::sort(
      full_time.begin(), full_time.end(),
      [](LARGE_INTEGER a, LARGE_INTEGER b) { return a.QuadPart < b.QuadPart; });
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    for (size_t i = 0; i < kSamples; ++i) {
      create_time[i].QuadPart = (create_time[i].QuadPart * 1000000) / freq.QuadPart;
      full_time[i].QuadPart = (full_time[i].QuadPart * 1000000) / freq.QuadPart;
    }
    std::cout << std::endl;
    std::cout << "CreateProcess times" << std::endl;
    std::cout << "  95th %%: " << create_time[percentile_index(kSamples, 95, 100)].QuadPart << " us" << std::endl;
    std::cout << "  99th %%: " << create_time[percentile_index(kSamples, 99, 100)].QuadPart << " us" << std::endl;
    std::cout << "  99.5th %%: " << create_time[percentile_index(kSamples, 995, 1000)].QuadPart << " us" << std::endl;
    std::cout << "  99.9th %%: " << create_time[percentile_index(kSamples, 999, 1000)].QuadPart << " us" << std::endl;
    std::cout << "  max: " << create_time[kSamples - 1].QuadPart << " us" << std::endl;
    std::cout << std::endl;
    std::cout << "CreateProcess + WaitForSingleObject times" << std::endl;
    std::cout << "  95th %%: " << full_time[percentile_index(kSamples, 95, 100)].QuadPart << " us" << std::endl;
    std::cout << "  99th %%: " << full_time[percentile_index(kSamples, 99, 100)].QuadPart << " us" << std::endl;
    std::cout << "  99.5th %%: " << full_time[percentile_index(kSamples, 995, 1000)].QuadPart << " us" << std::endl;
    std::cout << "  99.9th %%: " << full_time[percentile_index(kSamples, 999, 1000)].QuadPart << " us" << std::endl;
    std::cout << "  max: " << full_time[kSamples - 1].QuadPart << " us" << std::endl;
  }
  return 0;
}
