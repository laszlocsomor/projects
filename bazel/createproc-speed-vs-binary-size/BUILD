genrule(
    name = 'benchmark',
    outs = ['benchmark.txt'],
    cmd = '(for f in $(location :foo) $(location :foo-1M) $(location :foo-10M) $(location :foo-100M) $(location :foo-200M); do echo "## $$f"; for i in {1..5}; do $(location :createproc) $$f ; done ; echo ; done ; ) > $@',
    tools = [
        ':createproc',
        ':foo',
        ':foo-1M',
        ':foo-10M',
        ':foo-100M',
        ':foo-200M',
    ],
)

cc_binary(
    name = 'createproc',
    srcs = ['createproc.cc'],
    copts = ['-DUNICODE'],
)

cc_binary(
    name = 'foo',
    srcs = ['foo.cc'],
)

[genrule(
    name = 'foo-%dM' % i,
    srcs = ['foo'],
    outs = ['foo-%dM.exe' % i],
    output_to_bindir = 1,
    executable = 1,
    cmd = ('dd if=$< iflag=binary oflag=binary of=$@ &&' +
           'dd if=/dev/zero ibs=1000 count=%d iflag=binary oflag=append,binary conv=notrunc of=$@' % (i * 1000)),
) for i in [1, 10, 100, 200]]
