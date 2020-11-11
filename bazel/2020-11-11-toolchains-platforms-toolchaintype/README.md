# Bazel example for <https://github.com/bazelbuild/bazel/issues/6829>

Demonstrates usage of toolchains and platforms.

Tested with Bazel 3.7.0 on Ubuntu 20.04

## Structure

```
├── repo1             # Definition for the toolchains, platforms, and bar_binary
│   ├── bar_rules
│   │   ├── bar.bzl   # Implements bar_binary
│   │   └── BUILD     # Empty
│   ├── bar_tools
│   │   ├── bar_toolchain.bzl  # Implements the toolchain rule
│   │   └── BUILD     # Defines toolchains and platforms
│   ├── usage
│   │   ├── BUILD     # Example usage of bar_binary
│   │   └── x.bar     # Dummy .bar source
│   └── WORKSPACE     # Defines the "repo1" repository, registers toolchains
└── repo2
    ├── usage
    │   ├── BUILD     # Example usage of bar_binary in another repo
    │   └── x.bar     # Dummy .bar source
    └── WORKSPACE     # Defines the "repo1" external repo, registers toolchains
```

## Usage

### From repo1

```
  $ bazel build //usage:hello
(...)
(09:55:31) INFO: Build completed successfully, 1 total action

  $ cat bazel-bin/usage/hello.out 
linux-barc.bin
hello
```

```
  $ bazel build //usage:hello --host_platform=//bar_tools:windows_platform
(...)
(09:56:19) INFO: Build completed successfully, 2 total actions

  $ cat bazel-bin/usage/hello.out 
windows-barc.exe
hello
```

### From repo2

```
  $ bazel build //usage:hello
(...)
(09:56:58) INFO: Build completed successfully, 2 total actions

  $ cat bazel-bin/usage/hello.out 
linux-barc.bin
hello
```

```
  $ bazel build //usage:hello --host_platform=@repo1//bar_tools:windows_platform
(...)
(09:57:56) INFO: Build completed successfully, 2 total actions

  $ cat bazel-bin/usage/hello.out 
windows-barc.exe
hello
```
