genrule(
    name = "main",
    outs = ["main.txt"],
    srcs = ["dep.txt"],
    cmd = "cp $< $@",
)

genrule(
    name = "dep",
    outs = ["dep.txt"],
    srcs = ["input.txt"],
    tools = [":tool"],
    cmd = "$(location tool) $< $@",
)

java_binary(
    name = "tool",
    srcs = ["Tool.java"],
    main_class = "Tool",
)
