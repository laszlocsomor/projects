# Repro for [Bazel issue #6200](https://github.com/bazelbuild/bazel/issues/6200)

Though this is a bug in the `maven_server` rule implementation, you don't need a local webserver to
repro this bug with Bazel 0.23.0.

1. Open cmd.exe
2. `set HOME=d:`
3. `bazel build @thing_a_ma_bop//jar`

This will crash Bazel 0.23.0.

If you set `HOME=d:/`, the crash won't happen.
