# Demo: Bazel correctness bug on Windows

Bazel on Windows does not pick up the change of a Starlark file in an external
repository.

Usage:

1.  `bazel run //src:foo`

    This will build and run the target. Output should be something like:

        ...
        INFO: Build completed successfully, 4 total actions
        hello!

2.  Change `repo1/gen_cc.bzl` so the generated C++ file looks different.

    For example, change the `printf` call to print some other string than
    "hello!".

3.  `bazel run //src:foo` again.

    We expect Bazel to notice the change, and rebuild the `cc_binary` rule.

    However, Bazel still prints the old message:

        ...
        INFO: Build completed successfully, 4 total actions
        hello!

4.  Change `repo1/gen_cc.bzl` by changing the output file's name in the `rule()`
    call's `outputs` attribute from `%{name}-1.cc` to `%{name}-2.cc`.

5.  Try `bazel run //src:foo` again.

    Bazel still doesn't notice that the file changed, even though the
    `@repo2//:gen` rule now produces a different file than before!
