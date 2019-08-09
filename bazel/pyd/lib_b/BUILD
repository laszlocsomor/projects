# ----------------------------------------------------------------------
# @io_bazel//examples/windows/dll:windows_dll_library.bzl defines
# windows_dll_library, which does the same in one rule
# ----------------------------------------------------------------------

cc_binary(
    name = "b.dll",
    srcs = ["b.cc"],
    linkshared = 1,
    deps = ["//lib_a:interface_lib"],
)

filegroup(
    name = "b.lib",
    srcs = [":b.dll"],
    output_group = "interface_library",
)

cc_import(
    name = "interface_lib",
    visibility = ["//visibility:public"],
    interface_library = ":b.lib",
    shared_library = ":b.dll",
)

cc_library(
    name = "lib_b",
    visibility = ["//visibility:public"],
    deps = [
        ":interface_lib",
        "//lib_a:interface_lib",
    ],
)
