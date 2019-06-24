# Bazel bug: glob + exclude with incorrect path casing

Repro with Bazel 0.27.0:

```
bazel build //:x

type bazel-bin\x.txt
```

Output:

```
foo/Bar/x.txt foo/Bar/y.dat
```

y.dat should not be in the output, but it is.
