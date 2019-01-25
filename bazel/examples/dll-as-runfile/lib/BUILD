package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "mydll.dll",
    srcs = ["lib.cc"],
    deps = [":lib-hdrs"],
    linkshared = 1,
)

cc_library(
    name = "lib-hdrs",
    hdrs = ["lib.h"],
)
