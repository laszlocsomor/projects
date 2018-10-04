#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <iostream>

int64_t CurrentTimeNanos() {
  struct timespec ts = {};
  if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
    int err = errno;
    std::cerr << "ERROR: clock_gettime failed: " << err;
  }
  return {ts.tv_sec * 1000LL * 1000LL * 1000LL + ts.tv_nsec};
}

bool RunProc(char* argv0, int64_t* create_time, int64_t* full_time) {
  char arg[2] = {'x', 0};
  char* args[3] = {argv0, arg, NULL};

  int64_t start = CurrentTimeNanos();
  pid_t child = fork();
  if (child) {
    int64_t t1 = CurrentTimeNanos();
    int status;
    waitpid(child, &status, 0);
    int64_t t2 = CurrentTimeNanos();
    *create_time = t1 - start;
    *full_time = t2 - start;
  } else {
    execv(argv0, args);
  }
  return true;
}

size_t percentile_index(size_t total, size_t a, size_t b) {
  return std::min<size_t>(total - 1, (total * a) / b);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    static const size_t kSamples = 1000;
    std::array<int64_t, kSamples> create_time;
    std::array<int64_t, kSamples> full_time;
    for (size_t i = 0; i < kSamples; ++i) {
      if (!RunProc(argv[0], &create_time[i], &full_time[i])) {
        return 1;
      }
      if (i % 10 == 0) {
        std::cout << "ran " << i << " processes\r";
      }
    }
    for (size_t i = 0; i < kSamples; ++i) {
      create_time[i] /= 1000LL;
      full_time[i] /= 1000LL;
    }
    std::sort(create_time.begin(), create_time.end());
    std::sort(full_time.begin(), full_time.end());
    std::cout << std::endl;
    std::cout << "fork times" << std::endl;
    std::cout << "  95th %%: " << create_time[percentile_index(kSamples, 95, 100)] << " us" << std::endl;
    std::cout << "  99th %%: " << create_time[percentile_index(kSamples, 99, 100)] << " us" << std::endl;
    std::cout << "  99.5th %%: " << create_time[percentile_index(kSamples, 995, 1000)] << " us" << std::endl;
    std::cout << "  99.9th %%: " << create_time[percentile_index(kSamples, 999, 1000)] << " us" << std::endl;
    std::cout << "  max: " << create_time[kSamples - 1] << " us" << std::endl;
    std::cout << std::endl;
    std::cout << "fork + waitpid times" << std::endl;
    std::cout << "  95th %%: " << full_time[percentile_index(kSamples, 95, 100)] << " us" << std::endl;
    std::cout << "  99th %%: " << full_time[percentile_index(kSamples, 99, 100)] << " us" << std::endl;
    std::cout << "  99.5th %%: " << full_time[percentile_index(kSamples, 995, 1000)] << " us" << std::endl;
    std::cout << "  99.9th %%: " << full_time[percentile_index(kSamples, 999, 1000)] << " us" << std::endl;
    std::cout << "  max: " << full_time[kSamples - 1] << " us" << std::endl;
  }
  return 0;
}
