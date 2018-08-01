[cc_library(
    name = "r%d" % i,
    srcs = (["lib.cc"] if i < 512 else ["lib-leaf.cc"]),
    copts = ["-DIVALUE=%d" % i] + ([
        "-DDEP1=%d" % (i * 2),
        "-DDEP2=%d" % (i * 2 + 1),
    ] if i < 512 else []),
    deps = ([
        "r%d" % (i * 2),
        "r%d" % (i * 2 + 1),
    ] if i < 512 else []),
) for i in range(1, 1024)]

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = ["r1"],
)
