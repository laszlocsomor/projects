def _imp(repository_ctx):
    repository_ctx.file("BUILD", 'exports_files(["foo.sh", "foo.txt"])')

    repository_ctx.file(
        "foo.sh",
        """#!/bin/bash
echo "FOO(%s, ${FOO:-})"
echo "BAR(%s, ${BAR:-})"
""" % (
            repository_ctx.os.environ.get("FOO"),
            repository_ctx.os.environ.get("BAR"),
        ),
        executable = True,
    )

    res = repository_ctx.execute(
        ["bash", "-c", "./foo.sh"],
        environment = {"FOO": "fooA"},
    )

    repository_ctx.file("foo.txt", res.stdout)

repo = repository_rule(
    implementation = _imp,
    environ = ["FOO"],
    local = True,
)
