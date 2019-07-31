def _impl(ctx):
    tool = ctx.executable.tool
    print("type(tool)=%s" % type(tool))
    out = ctx.actions.declare_file(ctx.label.name + ".out")
    ctx.actions.run(
        outputs = [out],
        executable = tool,
        arguments = [out.path],
    )
    return [DefaultInfo(files = depset([out]))]

run_tool = rule(
    implementation = _impl,
    attrs = {
        "tool": attr.label(
            executable = True,
            allow_files = True,
            cfg = "host",
        ),
    },
)
