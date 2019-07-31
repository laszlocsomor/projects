load(":run_tool.bzl", "run_tool")

run_tool(
    name = "use-file",
    tool = "foo.sh",
)

run_tool(
    name = "use-tool",
    tool = ":foo-gen",
)

genrule(
    name = "foo-gen",
    outs = ["foo-gen.sh"],
    srcs = ["foo.sh"],
    executable = True,
    cmd = "cp $< $@",
)
