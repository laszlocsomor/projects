genrule(
    name = "x",
    outs = ["x.txt"],
    cmd = "( cat bazel-out/stable-status.txt ; echo '---' ; cat bazel-out/volatile-status.txt ; ) > $@",
)
