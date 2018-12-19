genrule(
    name = "x",
    srcs = [
        ":big-file1",
        ":big-file2",
    ],
    outs = ["x1.txt"],
    cmd = "( cat $(location :big-file1) $(location :big-file2) ; echo hello ; ) > $@",
)

genrule(
    name = 'big-file1',
    outs = ['big-file-100MB.txt'],
    output_to_bindir = 1,
    executable = 1,
    cmd = 'dd if=/dev/zero ibs=1000 count=100000 iflag=binary oflag=binary conv=notrunc of=$@ >&/dev/null',
)

genrule(
    name = 'big-file2',
    outs = ['big-file-200MB.txt'],
    output_to_bindir = 1,
    executable = 1,
    cmd = 'dd if=/dev/zero ibs=1000 count=200000 iflag=binary oflag=binary conv=notrunc of=$@ >&/dev/null',
)

