genrule(
    name = "x",
    srcs = glob(
        ["foo/**"],  # mind this is lower-case
        exclude = ["Foo/Bar/y.dat"],  # mind this is upper-case
    ),
    outs = ["x.txt"],
    cmd = "echo $(SRCS) > $@",
)
