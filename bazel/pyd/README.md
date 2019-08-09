# .pyd example

Context: https://github.com/bazelbuild/bazel/issues/2497

Files:
-   a exports `int foo(int x)` (returns `x` * 2)
-   b imports `foo`, exports `int bar(int y)` (returns `-foo(y)`)
-   main imports `bar`, prints `bar(argc)`
-   alice imports `bar`, exports `qux(x)` (returns `bar(x) * 10`)

`main.exe` loads `b.dll` which loads `a.dll`.

`alice.pyd` loads `b.dll` which loads `a.dll`.

## With Bazel

C++ works fine:

```
C:\...> bazel run //cc_app:main -- x y
``` 

Output is:

```
argc=3, bar(3)=-6
```

Python with .pyd doesn't work purely with Bazel, so I cheat. Everything builds
cleanly, except I can't get alice.pyd and a.dll and b.dll to be copied next to
the binary.

```
bazel build //py_app:main
set PYTHONPATH=bazel-bin\lib_alice
bazel-bin\py_app\main.exe
```

Output is:

```
alice.qux(3)=-60
```

## Without Bazel

1.  From Start Menu, run "x64 Native Tools Command Prompt for VC 2019" **OR** run `vcvarsall.bat`
2.  run `build_py2.bat` or `build_py3.bat` as you like
3.  run `cd _outs & main.exe x y & cd ..`

    Output is:
    ```
    argc=3, bar(3)=-6
    ```

4.  run `cd _outs & c:\Python37\python.exe main.py & cd ..`

    Output is:
    ```
    alice.qux(3)=-60
    ```
