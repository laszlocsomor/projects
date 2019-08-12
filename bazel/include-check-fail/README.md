# Demo: `#include` validation fail on Windows

Usage:

    cd ws
    bazel build //:main

On Linux, builds fine.

On Windows, fails:

    ERROR: C:/src/my-projects/bazel/include-check-fail/ws/BUILD:1:1: undeclared inclusion(s) in rule '//:main':
    this rule is missing dependency declarations for the following files included by 'main.cc':
      'foo/a.h'

Explanation: in C++ compilation action, main workspace is always an include path (`/I.`). Rule also
depends on `@repo//:a` so that is also an include path. Both `@__main__` and `@repo` have `foo/a.h`.
Rule means to include the file from `@repo` but because `/I.` comes before `/Iexternal/repo` the
compiler picks `__main__/foo/a.h` instead.
