# Usage

The repo rule only depends on FOO, yet both FOO and BAR are visible to it.
The script uses the forced value of FOO.

    export FOO=foo1
    export BAR=bar1
    bazel build //:y >&/dev/null && cat bazel-bin/y.txt 

    FOO(foo1, fooA)
    BAR(bar1, bar1)


Changing FOO's value correctly re-fetches the repo:

    export FOO=foo2
    bazel build //:y >&/dev/null && cat bazel-bin/y.txt
    # output
    FOO(foo2, fooA)
    BAR(bar1, bar1)


Changing BAR's value doesn't re-fetch because the repo doesn't formally depend on it:

    export BAR=bar2
    bazel build //:y >&/dev/null && cat bazel-bin/y.txt
    # output
    FOO(foo2, fooA)
    BAR(bar1, bar1)

Changing FOO's value again will refetch, and BAR is picked up:

    export FOO=foo3
    bazel build //:y >&/dev/null && cat bazel-bin/y.txt
    # output:
    FOO(foo3, fooA)
    BAR(bar2, bar2)
