extern "C" {
  __declspec(dllexport) int bar(int x);

  __declspec(dllimport) int foo(int x);
}

int bar(int x) { return -foo(x); }
