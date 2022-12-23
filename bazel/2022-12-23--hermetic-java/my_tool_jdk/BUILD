load("@bazel_tools//tools/jdk:local_java_repository.bzl", "local_java_runtime")

local_java_runtime(
    name = "my_jdk_runtime",
    java_home = None,
    runtime_name = "//:my_jdk_runtime",
    version = "19",
)

alias(
    name = "toolchain",
    actual = "runtime_toolchain_definition",
)
