package(default_visibility = ["//visibility:public"])

java_library(
    name = "foo",
    srcs = ["Foo.java"],
    deps = [":bar"],
)

java_library(
    name = "bar",
    srcs = ["Bar.java"],
    plugins = [":plugin"],
)

java_plugin(
    name = "plugin",
    generates_api = True,  # culprit
    processor_class = "common.AnnotProc",
    deps = [":annotproc"],
)

java_library(
    name = "annotproc",
    srcs = ["AnnotProc.java"],
)

