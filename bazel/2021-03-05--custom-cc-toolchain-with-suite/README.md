# Demo: hermetic C++ toolchain with `cc_toolchain_suite`

Usage:

```sh
bazel --ignore_all_rc_files build -s --toolchain_resolution_debug --crosstool_top=//:my-suite --cpu=targetcpu //:hello
```

The build will fail, but Bazel picks up the right compiler:

```
INFO: ToolchainResolution:     Type @bazel_tools//tools/cpp:toolchain_type: target platform @local_config_platform//:host: Rejected toolchain @local_config_cc//:cc-compiler-armeabi-v7a; mismatching values: arm, android
INFO: ToolchainResolution:   Type @bazel_tools//tools/cpp:toolchain_type: target platform @local_config_platform//:host: execution @local_config_platform//:host: Selected toolchain @local_config_cc//:cc-compiler-k8
INFO: ToolchainResolution: Target platform @local_config_platform//:host: Selected execution platform @local_config_platform//:host, type @bazel_tools//tools/cpp:toolchain_type -> toolchain @local_config_cc//:cc-compiler-k8
INFO: ToolchainResolution: Target platform @local_config_platform//:host: Selected execution platform @local_config_platform//:host, 
INFO: ToolchainResolution: Target platform @local_config_platform//:host: Selected execution platform @local_config_platform//:host, 
INFO: Analyzed target //:hello (15 packages loaded, 48 targets configured).
INFO: Found 1 target...
SUBCOMMAND: # //:hello [action 'Compiling hello.cc', configuration: 46ae0b204f5c73011fd3320fff8d749dff64dd961d9696787fee3f30bcb8de7d, execution platform: @local_config_platform//:host]
(cd /home/laszlo/.cache/bazel/_bazel_laszlo/90d6a1d4094c950846990307844ab182/execroot/__main__ && \
  exec env - \
    PATH=/home/laszlo/app:/home/laszlo/app:/home/laszlo/google-cloud-sdk/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/laszlo/app/google-cloud-sdk/bin:/home/laszlo/app/google-cloud-sdk/bin \
    PWD=/proc/self/cwd \
  /dummy/tool/path -MD -MF bazel-out/targetcpu-fastbuild/bin/_objs/hello/hello.pic.d '-frandom-seed=bazel-out/targetcpu-fastbuild/bin/_objs/hello/hello.pic.o' -fPIC -iquote . -iquote bazel-out/targetcpu-fastbuild/bin -iquote external/bazel_tools -iquote bazel-out/targetcpu-fastbuild/bin/external/bazel_tools -c hello.cc -o bazel-out/targetcpu-fastbuild/bin/_objs/hello/hello.pic.o)
ERROR: /home/laszlo/stuff/my-projects/bazel/2021-03-05--custom-cc-toolchain-with-suite/BUILD:3:10: Compiling hello.cc failed: (Exit 1): path failed: error executing command /dummy/tool/path -MD -MF bazel-out/targetcpu-fastbuild/bin/_objs/hello/hello.pic.d '-frandom-seed=bazel-out/targetcpu-fastbuild/bin/_objs/hello/hello.pic.o' -fPIC -iquote . -iquote ... (remaining 9 argument(s) skipped)

Use --sandbox_debug to see verbose messages from the sandbox path failed: error executing command /dummy/tool/path -MD -MF bazel-out/targetcpu-fastbuild/bin/_objs/hello/hello.pic.d '-frandom-seed=bazel-out/targetcpu-fastbuild/bin/_objs/hello/hello.pic.o' -fPIC -iquote . -iquote ... (remaining 9 argument(s) skipped)

Use --sandbox_debug to see verbose messages from the sandbox
src/main/tools/linux-sandbox-pid1.cc:390: "execvp(/dummy/tool/path, 0x1b62fc0)": No such file or directory
```
