# Demo: build a DLL and use from a `cc_binary`

This example only works on Windows. It's an extended version of
https://github.com/bazelbuild/bazel/tree/master/examples/windows/dll

Usage:

    bazel run //src:main

Output:

    Loaded DLL from path: \\?\C:\_bazel\tlrnaj7b\execroot\__main__\bazel-out\x64_windows-fastbuild\bin\lib\mydll.dll
    myfunc(5) = 10
