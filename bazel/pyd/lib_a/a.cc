extern "C" {
  __declspec(dllexport) int foo(int x);
}

int foo(int x) { return x * 2; }
