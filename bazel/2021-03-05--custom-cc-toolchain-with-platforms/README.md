# Demo: hermetic C++ toolchain with `toolchain()`

Usage:

```sh
bazel --ignore_all_rc_files build -s --toolchain_resolution_debug --extra_execution_platforms=//:exec-platform --platforms=//:target-platform --incompatible_enable_cc_toolchain_resolution //:hello
```

The build will fail, but Bazel picks up the right compiler:

```
INFO: ToolchainResolution:   Type @bazel_tools//tools/cpp:toolchain_type: target platform //:target-platform: execution //:exec-platform: Selected toolchain //:my_toolchain
INFO: ToolchainResolution:     Type @bazel_tools//tools/cpp:toolchain_type: execution platform @local_config_platform//:host: Rejected toolchain //:my_toolchain; mismatching values: execcpu, execos
INFO: ToolchainResolution:     Type @bazel_tools//tools/cpp:toolchain_type: target platform //:target-platform: Rejected toolchain @local_config_cc//:cc-compiler-armeabi-v7a; mismatching values: arm, android
INFO: ToolchainResolution:     Type @bazel_tools//tools/cpp:toolchain_type: target platform //:target-platform: Rejected toolchain @local_config_cc//:cc-compiler-k8; mismatching values: x86_64, linux
INFO: ToolchainResolution: Target platform //:target-platform: Selected execution platform //:exec-platform, type @bazel_tools//tools/cpp:toolchain_type -> toolchain //:my_toolchain
INFO: ToolchainResolution: Target platform @local_config_platform//:host: Selected execution platform //:exec-platform, 
INFO: ToolchainResolution: Target platform //:target-platform: Selected execution platform //:exec-platform, 
INFO: Analyzed target //:hello (15 packages loaded, 61 targets configured).

...

SUBCOMMAND: # //:hello [action 'Compiling hello.cc', configuration: b8155d237980b66722f14de09c8ac53442ee11beece960548dd6ea7a43a86243, execution platform: //:exec-platform]
(cd /home/laszlo/.cache/bazel/_bazel_laszlo/808a5f37ae78ceb7ec533a1f5fd66937/execroot/__main__ && \
  exec env - \
    PATH=/home/laszlo/app:/home/laszlo/app:/home/laszlo/google-cloud-sdk/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/laszlo/app/google-cloud-sdk/bin:/home/laszlo/app/google-cloud-sdk/bin \
    PWD=/proc/self/cwd \
  /dummy/tool/path -MD -MF bazel-out/k8-fastbuild/bin/_objs/hello/hello.pic.d '-frandom-seed=bazel-out/k8-fastbuild/bin/_objs/hello/hello.pic.o' -fPIC -iquote . -iquote bazel-out/k8-fastbuild/bin -iquote external/bazel_tools -iquote bazel-out/k8-fastbuild/bin/external/bazel_tools -c hello.cc -o bazel-out/k8-fastbuild/bin/_objs/hello/hello.pic.o)
ERROR: /home/laszlo/stuff/my-projects/bazel/2021-03-05--custom-cc-toolchain-with-platforms/BUILD:3:10: Compiling hello.cc failed: (Exit 1): path failed: error executing command /dummy/tool/path -MD -MF bazel-out/k8-fastbuild/bin/_objs/hello/hello.pic.d '-frandom-seed=bazel-out/k8-fastbuild/bin/_objs/hello/hello.pic.o' -fPIC -iquote . -iquote bazel-out/k8-fastbuild/bin -iquote ... (remaining 7 argument(s) skipped)

Use --sandbox_debug to see verbose messages from the sandbox path failed: error executing command /dummy/tool/path -MD -MF bazel-out/k8-fastbuild/bin/_objs/hello/hello.pic.d '-frandom-seed=bazel-out/k8-fastbuild/bin/_objs/hello/hello.pic.o' -fPIC -iquote . -iquote bazel-out/k8-fastbuild/bin -iquote ... (remaining 7 argument(s) skipped)

Use --sandbox_debug to see verbose messages from the sandbox
src/main/tools/linux-sandbox-pid1.cc:390: "execvp(/dummy/tool/path, 0xe5ffc0)": No such file or directory
```
