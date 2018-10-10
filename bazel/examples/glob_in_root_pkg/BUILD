genrule(
    name = "x",
    outs = ["x.txt"],
    srcs = glob(["**/*.txt"]),
    cmd = "echo $(SRCS) > $@",
)
