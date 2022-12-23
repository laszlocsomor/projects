# Build java 19:
#   bazel build //:app --java_language_version=19
#
# Run with java 19:
#   JAVA_HOME=$PWD/zulu19.30.11-ca-jdk19.0.1-linux_x64  bazel run //:app  --java_language_version=19
#
# Run with Bazel-supported java 17:
#   bazel run //:app  --java_language_version=17 --java_runtime_version=remotejdk_17
#
#   Supported values of --java_runtime_version are localjdk, localjdk_[version], remotejdk_11, and
#   remote_jdk17.  (https://bazel.build/docs/user-manual#java-runtime-version)
#
# Build as tool with Bazel-supported java 17:
#   bazel build //:x  --java_language_version=17 --java_runtime_version=remotejdk_17 --tool_java_language_version=17 --tool_java_runtime_version=remotejdk_17
#
# Build as tool with java 19:
#   bazel build //:x  --java_language_version=19 --java_runtime_version=19 --tool_java_language_version=19 --tool_java_runtime_version=19

genrule(
    name = "x",
    outs = ["x.out"],
    cmd = "$(location :app) x > $@",
    tools = [":app"],
)

java_library(
    name = "app_lib",
    srcs = ["Main.java"],
)

java_binary(
    name = "app",
    main_class = "Main",
    runtime_deps = [":app_lib"],
)

load(
    "@bazel_tools//tools/jdk:default_java_toolchain.bzl",
    "BASE_JDK9_JVM_OPTS",
    "DEFAULT_JAVACOPTS",
    "DEFAULT_TOOLCHAIN_CONFIGURATION",
    "default_java_toolchain",
)

default_java_toolchain(
    name = "my_jdk",
    configuration = DEFAULT_TOOLCHAIN_CONFIGURATION,
    java_runtime = ":my_jdk_runtime",
    javacopts = DEFAULT_JAVACOPTS,
    jvm_opts = BASE_JDK9_JVM_OPTS,
    source_version = "19",
    target_version = "19",
)

java_runtime(
    name = "my_jdk_runtime",
    srcs = ["@my_jdk//:files"],
    java = "@my_jdk//:bin/java",
)

