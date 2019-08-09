load("@bazel_skylib//rules:copy_file.bzl", "copy_file")

cc_binary(
    name = "alice.dll",
    srcs = ["alice.cc"],
    linkshared = 1,
    deps = [
        "//lib_b",
        "@local_py3//:py3",
    ],
)

filegroup(
    name = "alice_dlls",
    srcs = [":alice.dll"],
    output_group = "runtime_dynamic_libraries",
)

copy_file(
    name = "alice_pyd",
    src = "alice.dll",
    out = "alice.pyd",
)

filegroup(
    name = "lib_alice",
    srcs = [
        ":alice_pyd",
        ":alice_dlls",
    ],
    visibility = ["//visibility:public"],
)
