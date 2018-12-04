## Demo for enabling/disabling MSYS path conversion

`bazel run //:runprog`

This will run a program with path conversion, then without path conversion.

### Output

```
C:\src\my-projects\bazel\msys-path-conv>bazel run //:runprog
...

PRINTARG=C:/_bazel/2q36zgcv/execroot/msys_path_conv/bazel-out/x64_windows-fastbuild/bin/printarg.exe
MSYS2_ARG_CONV_EXCL=
argc=7
argv[0]=(C:\_bazel\2q36zgcv\execroot\msys_path_conv\bazel-out\x64_windows-fastbuild\bin\printarg.exe)
argv[1]=(begin)
argv[2]=(nul)
argv[3]=(C:/msys64/usr/bin/sh)
argv[4]=(C:/src)
argv[5]=(C:/msys64/hello)
argv[6]=(end)
MSYS2_ARG_CONV_EXCL=*
argc=7
argv[0]=(C:\_bazel\2q36zgcv\execroot\msys_path_conv\bazel-out\x64_windows-fastbuild\bin\printarg.exe)
argv[1]=(begin)
argv[2]=(/dev/null)
argv[3]=(/bin/sh)
argv[4]=(/c/src)
argv[5]=(/hello)
argv[6]=(end)
```
