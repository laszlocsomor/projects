# Starlark bug: ctx.actions.run(executable) can't use source file

Even though `foo.sh` has 0777 permission, ctx.actions.run cannot use it as the executable.

Using a source file tool fails:
```
  $ bazel build --verbose_failures //:use-file
(...)
DEBUG: /usr/local/google/home/laszlocsomor/stuff/my-projects/bazel/ctx_actions_run_with_file/run_tool.bzl:3:5: type(tool)=File
INFO: Analyzed target //:use-file (4 packages loaded, 17 targets configured).
INFO: Found 1 target...
ERROR: /usr/local/google/home/laszlocsomor/stuff/my-projects/bazel/ctx_actions_run_with_file/BUILD:3:1: Action use-file.out failed (Exit 1) foo.sh failed: error executing command 
  (cd /usr/local/google/home/laszlocsomor/.cache/bazel/_bazel_laszlocsomor/0effd9a875a6d89eefdce66b1a117712/sandbox/linux-sandbox/5/execroot/__main__ && \
  exec env - \
  foo.sh bazel-out/k8-fastbuild/bin/use-file.out)
Execution platform: @bazel_tools//platforms:host_platform

Use --sandbox_debug to see verbose messages from the sandbox
src/main/tools/linux-sandbox-pid1.cc:427: "execvp(foo.sh, 0x16ea8d0)": No such file or directory
```

But using a generated file tool works:
```
  $ bazel build //:use-tool
(...)
DEBUG: /usr/local/google/home/laszlocsomor/stuff/my-projects/bazel/ctx_actions_run_with_file/run_tool.bzl:3:5: type(tool)=File
INFO: Analyzed target //:use-tool (0 packages loaded, 0 targets configured).
INFO: Found 1 target...
Target //:use-tool up-to-date:
  bazel-bin/use-tool.out
```
