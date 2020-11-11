BarcInfo = provider(
    fields = ["compiler_name"],
)

def _impl(ctx):
    toolchain_info = platform_common.ToolchainInfo(
        barcinfo = BarcInfo(
            compiler_name = ctx.attr.compiler_name,
        ),
    )
    return [toolchain_info]

bar_toolchain = rule(
    implementation = _impl,
    attrs = {
        "compiler_name": attr.string(),
    },
)
