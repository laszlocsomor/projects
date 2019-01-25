#include <windows.h>

#include <iostream>
#include <string>
#include <memory>

#include "tools/cpp/runfiles/runfiles.h"
using bazel::tools::cpp::runfiles::Runfiles;

typedef int (*LPMYDLL_FUNC)(int);

std::wstring AsWindowsPath(const std::string& abs_utf8_path) {
  int wstr_size = MultiByteToWideChar(CP_UTF8, 0, abs_utf8_path.c_str(), -1, NULL, 0);
  std::unique_ptr<WCHAR[]> wpath(new WCHAR[wstr_size + 4]);
  wpath[0] = L'\\';
  wpath[1] = L'\\';
  wpath[2] = L'?';
  wpath[3] = L'\\';
  MultiByteToWideChar(CP_UTF8, 0, abs_utf8_path.c_str(), -1, &wpath[4], wstr_size);
  for (WCHAR* c = &wpath[4]; *c; ++c) {
    if (*c == L'/') {
      *c = L'\\';
    }
  }
  return wpath.get();
}

int main(int argc, char** argv) {
  std::string error;
  std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0], &error));
  if (!runfiles) {
    std::cerr << "ERROR: failed to init runfiles, error: " << error << std::endl;
    return 1;
  }

  // __main__ is the default workspace name.
  // Since the WORKSPACE file has no workspace() rule, the workspace is unnamed, so its name is
  // __main__.
  // If there were a workspace(name = "foo") rule, we'd use "foo" instead of "__main__" below.
  std::string rloc = runfiles->Rlocation("__main__/lib/mydll.dll");
  if (rloc.empty()) {
    std::cerr << "ERROR: could not find runfile path" << std::endl;
    return 1;
  }
  std::wstring wrloc = AsWindowsPath(rloc);

  HMODULE dll = LoadLibraryW(wrloc.c_str());
  if (dll == NULL) {
    DWORD err = GetLastError();
    std::cerr << "ERROR: failed to load DLL, error: " << err << ", path: ";
    std::wcerr << wrloc << std::endl;
    return 1;
  }

  std::cout << "Loaded DLL from path: ";
  std::wcout << wrloc << std::endl;

  LPMYDLL_FUNC myfunc = reinterpret_cast<LPMYDLL_FUNC>(GetProcAddress(dll, "mydll_func"));
  if (myfunc == NULL) {
    DWORD err = GetLastError();
    std::cerr << "ERROR: failed to load function, error: " << err << std::endl;
    FreeLibrary(dll);
    return 1;
  } 

  std::cout << "myfunc(5) = " << myfunc(5) << std::endl;
  FreeLibrary(dll);

  return 0;
}

