# ----------------------------------------------------------------------
# @io_bazel//examples/windows/dll:windows_dll_library.bzl defines
# windows_dll_library, which does the same in one rule
# ----------------------------------------------------------------------

cc_binary(
    name = "a.dll",
    srcs = ["a.cc"],
    linkshared = 1,
)

filegroup(
    name = "a.lib",
    srcs = [":a.dll"],
    output_group = "interface_library",
)

cc_import(
    name = "interface_lib",
    visibility = ["//visibility:public"],
    interface_library = ":a.lib",
    shared_library = ":a.dll",
)

cc_library(
    name = "lib_a",
    visibility = ["//visibility:public"],
    deps = [":interface_lib"],
)
