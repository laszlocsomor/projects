# Demo: passing command line args

The code passes args to a subprocess (`args.bat`), demonstrating how they arrive
to the subprocess.

The only transformation the code does is replacing the empty string argument
with two double quotes. No further quoting or escaping is done.

## To run the program
```
C:\src\my-projects\bazel\pass-args>bazel run //:main 2>nul -- c:\src\my-projects\bazel\pass-args\args.bat
```

## The unprocessed arguments
```
INFO(main.cc:46) AddCommandLineArg(c:\src\my-projects\bazel\pass-args\args.bat)
INFO(main.cc:46) AddCommandLineArg(foo)
INFO(main.cc:46) AddCommandLineArg(a b)
INFO(main.cc:46) AddCommandLineArg("a b")
INFO(main.cc:46) AddCommandLineArg()
INFO(main.cc:46) AddCommandLineArg("")
INFO(main.cc:46) AddCommandLineArg(bar)
INFO(main.cc:46) AddCommandLineArg("baz")
INFO(main.cc:46) AddCommandLineArg(last)
```

## The command line for `CreateProcessW`
```
INFO(main.cc:125) cmdline for CreateProcessW: {c:\src\my-projects\bazel\pass-args\args.bat foo a b "a b" "" "" bar "baz" last}
```

## The output from `args.bat`
```
--- Hello from args.bat ---
arg0=(c:\src\my-projects\bazel\pass-args\args.bat)
arg1=(foo)
arg2=(a)
arg3=(b)
arg4=("a b")
arg5=("")
arg6=("")
arg7=(bar)
arg8=("baz")
arg9=(last)
```
