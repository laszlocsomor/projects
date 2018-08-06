[java_library(
    name = "lib%d" % i,
    srcs = ["Foo%d.java" % i],
#    copts = ["-DIVALUE=%d" % i] + ([
#        "-DDEP1=%d" % (i * 2),
#        "-DDEP2=%d" % (i * 2 + 1),
#    ] if i < 512 else []),
    deps = ([
        "lib%d" % (i * 2),
        "lib%d" % (i * 2 + 1),
    ] if i < 512 else []),
) for i in range(1, 1024)]

java_binary(
    name = "main",
    main_class = "Main",
    srcs = ["Main.java"],
    # copts = ["-DROOTVALUE=1"],
    deps = ["lib1"],
)
