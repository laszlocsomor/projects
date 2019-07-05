genrule(
    name = "y",
    srcs = ["@x//:foo.txt"],
    outs = ["y.txt"],
    #cmd = "$(location @x//:foo.sh) > $@",
    cmd = "cp $< $@",
)
