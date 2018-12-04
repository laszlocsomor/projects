cc_binary(
    name = "printarg",
    srcs = ["printarg.cc"],
)

sh_binary(
    name = "runprog",
    srcs = ["runprog.sh"],
    deps = ["@bazel_tools//tools/bash/runfiles"],
    data = [":printarg"],
)
