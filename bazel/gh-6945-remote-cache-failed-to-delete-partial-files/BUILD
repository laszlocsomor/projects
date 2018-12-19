genrule(
    name = "x",
    srcs = [
        ":big-file",
    ],
    outs = ["x1.txt"],
    cmd = "( cat $< ; echo hello ; ) > $@",
)

genrule(
    name = 'big-file',
    outs = ['big-file-100MB.txt'],
    output_to_bindir = 1,
    executable = 1,
    cmd = 'dd if=/dev/zero ibs=1000 count=100000 iflag=binary oflag=binary conv=notrunc of=$@ >&/dev/null',
)

