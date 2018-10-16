genrule(
    name = "x",
    outs = ["x.txt"],
    stamp = 1,
    cmd = "( cat bazel-out/stable-status.txt ; echo '---' ; cat bazel-out/volatile-status.txt ; ) > $@",
)
