# .pyd example

Files:
-   a exports `int foo(int x)` (returns `x` * 2)
-   b imports `foo`, exports `int bar(int y)` (returns `-foo(y)`)
-   main imports `bar`, prints `bar(argc)`
-   alice imports `bar`, exports `qux(x)` (returns `bar(x) * 10`)

`main.exe` loads `b.dll` which loads `a.dll`.

`alice.pyd` loads `b.dll` which loads `a.dll`.

1.  From Start Menu, run "x64 Native Tools Command Prompt for VC 2019" **OR** run `vcvarsall.bat`
2.  run `build_py2.bat` or `build_py3.bat` as you like
3.  run `cd _outs & main.exe x y & cd ..` (should output -6 (`argc` * 2 * -1))
4.  run `cd _outs & c:\Python37\python.exe main.py & cd ..` (should output -60)
