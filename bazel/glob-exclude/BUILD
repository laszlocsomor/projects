genrule(
    name = "x",
    srcs = glob(
        # Uses GlobFunc for "foo" (simple pattern), but not for "f*o*o"
        # (complext pattern).
        #["foo/**"],  # mind this is lower-case
        ["foo/*/baz/**"],
        exclude = [
            "Foo/Bar/Baz/Qux/y.dat",
        ],  # mind this is upper-case
    ),
    outs = ["x.txt"],
    cmd = "echo $(SRCS) > $@",
)
