[genrule(
    name = "r%d" % i,
    srcs = (["r%d" % (i * 2), "r%d" % (i*2 + 1)] if i < 512 else []),
    outs = ["r%d.out" % i],
    cmd = ("echo \"idx=%d deps=%d,%d\" > $@" % (i, i*2, i*2 + 1)
           if i < 512 else
           "echo \"idx=%d leaf\" > $@" % i),
 ) for i in range(1, 1025)]
