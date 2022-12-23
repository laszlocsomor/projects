def _impl(repository_ctx):
    repository_ctx.extract(
        repository_ctx.attr.src,
        stripPrefix = repository_ctx.attr.strip_prefix,
    )

    repository_ctx.file(
        "BUILD",
        content = """# Generated by local_repository_archive rule
package(default_visibility = ["//visibility:public"])

_FILES = glob(["**"])

filegroup(
    name = "files",
    srcs = _FILES,
)

exports_files(_FILES)
""",
        executable = False,
    )

local_repository_archive = repository_rule(
    implementation = _impl,
    attrs = {
        "src": attr.label(mandatory = True, allow_single_file = True),
        "strip_prefix": attr.string(),
    },
)
