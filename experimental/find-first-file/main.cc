#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>

#include <string>

using std::string;

bool expand_wildcards(const string& path) {
  static const string kDot = ".";
  static const string kDotDot = "..";
  WIN32_FIND_DATAA metadata;
  HANDLE handle = ::FindFirstFileA(path.c_str(), &metadata);
  if (handle == INVALID_HANDLE_VALUE) {
    printf("DEBUG: expand(%s), handle invalid\n", path.c_str());
    return false;
  }

  string::size_type pos = path.find_last_of("\\/");
  string dirname;
  if (pos != string::npos) {
    dirname = path.substr(0, pos + 1);
  }
  printf("DEBUG: dirname=(%s)\n", dirname.c_str());

  do {
    if ((metadata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0
        && kDot != metadata.cFileName && kDotDot != metadata.cFileName) {
      if (!dirname.empty()) {
        printf("DEBUG: expand(%s) -> (%s%s)\n", path.c_str(), dirname.c_str(), metadata.cFileName);
      } else {
        printf("DEBUG: expand(%s) -> (%s)\n", path.c_str(), metadata.cFileName);
      }
      // consume
    }
  } while (::FindNextFileA(handle, &metadata));
    printf("DEBUG: expand(%s), done\n", path.c_str());
  FindClose(handle);
  return true;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    return 1;
  }
  expand_wildcards(argv[1]);
  return 0;
}
