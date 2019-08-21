# Demo

Issue: Bazel on Windows supports 8dot3 paths as package names. While packages refer to directories, they don't mean directories, and Bazel should require the full directory name be used in labels.

Repro:

    bazel build //long_p~1:x


