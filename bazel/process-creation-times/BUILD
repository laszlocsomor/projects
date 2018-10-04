cc_binary(
    name = "bin",
    srcs = select({
        "@bazel_tools//src/conditions:windows": ["createproc-win.cc"],
        "//conditions:default": ["createproc-linux.cc"],
    }),
)
