# Demonstrate output reporting from a slow repo rule

Bazel 0.18.0 on Windows only reports output from repository rules once the rule
completed. There's also no progress reporting for slow commands ran by
`repository_ctx.execute`.

Usage:

1. `bazel build //:sleep`
2. `copy bazel-bin\sleep.exe .`
3. edit slow\_repo rule's `sleep_bin` and `slept_txt` attributes in WORKSPACE file
4. `bazel --client_debug query @slow//:*`
5. observe that the file at the `slept_txt` path exists and contains entries for
   each second slept
