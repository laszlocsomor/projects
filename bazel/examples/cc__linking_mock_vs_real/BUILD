cc_library(
    name = "interface",
    hdrs = ["a.h"],
)

cc_library(
    name = "real-impl",
    srcs = ["a-real.cc"],
    deps = [":interface"],
)

cc_library(
    name = "mock-impl",
    srcs = ["a-mock.cc"],
    deps = [":interface"],
)

cc_binary(
    name = "bin",
    srcs = ["bin.cc"],
    deps = [
        ":interface",
        ":mock-impl",
        ":real-impl",
    ],
)
