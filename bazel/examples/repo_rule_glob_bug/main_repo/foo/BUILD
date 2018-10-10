genrule(
    name = "x",
    outs = ["x.txt"],
    srcs = ["@external_repo//:files"],
    cmd = "echo $(SRCS) > $@",
)

genrule(
    name = "y",
    outs = ["y.txt"],
    srcs = glob(["**/*.txt"]),
    cmd = "echo $(SRCS) > $@",
)
