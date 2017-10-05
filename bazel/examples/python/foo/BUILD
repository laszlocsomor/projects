py_binary(
    name = "foo_bin",
    srcs = ["foo_bin.py"],
    deps = ["//examples/python/foo/bar:bar_lib"],
    visibility = ["//examples/python/foo/baz:__pkg__"],
    data = ["foo-data.txt"],
)
