genrule(
    name = "benchmark",
    srcs = ["raw-data.txt"],
    outs = ["results.txt"],
    cmd = "$(location compute-percentiles) $< > $@",
    tools = [":compute-percentiles"],
)

genrule(
    name = "raw-data",
    outs = ["raw-data.txt"],
    cmd = ("for i in {1..1001}; do date +\"%s %N\" ; done > $@ &&" +
           "sed -i 's, \\([0-9]\\{6\\}\\)[0-9]*$$,\\1,' $@"),
)

py_binary(
    name = "compute-percentiles",
    srcs = ["cp.py"],
    main = "cp.py",
)
