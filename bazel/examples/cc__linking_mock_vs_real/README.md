# Demo: mocking out implementations in `cc_*` rules

Demonstrate how a `cc_binary` can depend on the real and on the mock implementation of some
interface, and how changing the order of the libraries in `cc_binary.deps` makes the linker pick one
or the other library.

To see the effects:

    bazel run //:bin -- a b c
    ...
    foo(4)=8

The binary was using `a-real.cc` because the `cc_binary` rule's `deps` attribute declared
`:real-impl` before `:mock-impl`:

    cc_binary(
        name = "bin",
        srcs = ["bin.cc"],
        deps = [
            ":interface",
            ":real-impl",
            ":mock-impl",
        ],
    )

This means the linker command line contains `libreal-impl.o` before `libmock-impl.o`.

Now edit the `BUILD` file and swap the two libraries in the `deps` attribute:

    cc_binary(
        name = "bin",
        srcs = ["bin.cc"],
        deps = [
            ":interface",
            ":real-impl",
            ":mock-impl",
        ],
    )

Re-run the binary:

    bazel run //:bin -- a b c
    ...
    foo(4)=42

Now the binary was using the mock implementation.
