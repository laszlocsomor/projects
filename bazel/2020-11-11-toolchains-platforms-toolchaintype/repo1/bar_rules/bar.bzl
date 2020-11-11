def _impl(ctx):
    info = ctx.toolchains["@repo1//bar_tools:toolchain_type"].barcinfo
    out = ctx.actions.declare_file("%s.out" % ctx.label.name)
    ctx.actions.run_shell(
        inputs = [ctx.file.src],
        outputs = [out],
        command = "(echo $1 ; cat $2 ; ) > $3",
        arguments = [info.compiler_name, ctx.file.src.path, out.path],
    )
    return [DefaultInfo(files = depset([out]))]

bar_binary = rule(
    implementation = _impl,
    attrs = {
        "src": attr.label(allow_single_file = True),
    },
    toolchains = ["@repo1//bar_tools:toolchain_type"]
)
