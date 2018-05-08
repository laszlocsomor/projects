# CreateProcess speed vs. binary size

Measure how the size of a binary affects the speed of `CreateProcess` on Windows.

Findings:

*   The first run is slower then the subsequent ones. I believe the reason is
    Windows Defender or some other security software scanning the binaries for
    malware.
*   Binary size correlates with `CreateProcess` wall time (the bigger the binary
    the slower it is to start), but only on the first run. On subsequent runs
    the binary size doesn't make a difference.


Results on my Windows machine (Intel Xeon E5-1650 v2 @ 3.50GHz, 32GB
RAM, HDD, Windows 10 version 1607):

```
## bazel-out/host/bin/foo.exe
CreateProcess took 43492 us (duration=148299 ticks, freq=3409754 ticks/sec)
CreateProcess took 3630 us (duration=12379 ticks, freq=3409754 ticks/sec)
CreateProcess took 3767 us (duration=12846 ticks, freq=3409754 ticks/sec)
CreateProcess took 3469 us (duration=11829 ticks, freq=3409754 ticks/sec)
CreateProcess took 3582 us (duration=12217 ticks, freq=3409754 ticks/sec)

## bazel-out/host/bin/foo-1M.exe
CreateProcess took 16578 us (duration=56528 ticks, freq=3409754 ticks/sec)
CreateProcess took 3685 us (duration=12568 ticks, freq=3409754 ticks/sec)
CreateProcess took 3449 us (duration=11761 ticks, freq=3409754 ticks/sec)
CreateProcess took 3430 us (duration=11696 ticks, freq=3409754 ticks/sec)
CreateProcess took 3770 us (duration=12856 ticks, freq=3409754 ticks/sec)

## bazel-out/host/bin/foo-10M.exe
CreateProcess took 16333 us (duration=55693 ticks, freq=3409754 ticks/sec)
CreateProcess took 3466 us (duration=11820 ticks, freq=3409754 ticks/sec)
CreateProcess took 3468 us (duration=11827 ticks, freq=3409754 ticks/sec)
CreateProcess took 3295 us (duration=11238 ticks, freq=3409754 ticks/sec)
CreateProcess took 3463 us (duration=11808 ticks, freq=3409754 ticks/sec)

## bazel-out/host/bin/foo-100M.exe
CreateProcess took 466867 us (duration=1591902 ticks, freq=3409754 ticks/sec)
CreateProcess took 8231 us (duration=28066 ticks, freq=3409754 ticks/sec)
CreateProcess took 3306 us (duration=11274 ticks, freq=3409754 ticks/sec)
CreateProcess took 3456 us (duration=11786 ticks, freq=3409754 ticks/sec)
CreateProcess took 3291 us (duration=11224 ticks, freq=3409754 ticks/sec)

## bazel-out/host/bin/foo-200M.exe
CreateProcess took 549073 us (duration=1872205 ticks, freq=3409754 ticks/sec)
CreateProcess took 3569 us (duration=12170 ticks, freq=3409754 ticks/sec)
CreateProcess took 3229 us (duration=11011 ticks, freq=3409754 ticks/sec)
CreateProcess took 3257 us (duration=11106 ticks, freq=3409754 ticks/sec)
CreateProcess took 3513 us (duration=11980 ticks, freq=3409754 ticks/sec)
```

Results on a Windows VM in GCP (Intel Xeon @ 2.20GHz, 7.5GB RAM, SSD, Windows
2016 Datacenter version 1607):

```
## bazel-out/host/bin/foo.exe
CreateProcess took 6049 us (duration=12995 ticks, freq=2148262 ticks/sec)
CreateProcess took 4424 us (duration=9506 ticks, freq=2148262 ticks/sec)
CreateProcess took 4610 us (duration=9904 ticks, freq=2148262 ticks/sec)
CreateProcess took 5268 us (duration=11319 ticks, freq=2148262 ticks/sec)
CreateProcess took 4786 us (duration=10282 ticks, freq=2148262 ticks/sec)

## bazel-out/host/bin/foo-1M.exe
CreateProcess took 6570 us (duration=14115 ticks, freq=2148262 ticks/sec)
CreateProcess took 4396 us (duration=9444 ticks, freq=2148262 ticks/sec)
CreateProcess took 4348 us (duration=9342 ticks, freq=2148262 ticks/sec)
CreateProcess took 4004 us (duration=8602 ticks, freq=2148262 ticks/sec)
CreateProcess took 4474 us (duration=9613 ticks, freq=2148262 ticks/sec)

## bazel-out/host/bin/foo-10M.exe
CreateProcess took 7374 us (duration=15843 ticks, freq=2148262 ticks/sec)
CreateProcess took 4799 us (duration=10311 ticks, freq=2148262 ticks/sec)
CreateProcess took 4419 us (duration=9494 ticks, freq=2148262 ticks/sec)
CreateProcess took 4908 us (duration=10544 ticks, freq=2148262 ticks/sec)
CreateProcess took 4341 us (duration=9327 ticks, freq=2148262 ticks/sec)

## bazel-out/host/bin/foo-100M.exe
CreateProcess took 23249 us (duration=49947 ticks, freq=2148262 ticks/sec)
CreateProcess took 4394 us (duration=9441 ticks, freq=2148262 ticks/sec)
CreateProcess took 8827 us (duration=18963 ticks, freq=2148262 ticks/sec)
CreateProcess took 5082 us (duration=10918 ticks, freq=2148262 ticks/sec)
CreateProcess took 8264 us (duration=17755 ticks, freq=2148262 ticks/sec)

## bazel-out/host/bin/foo-200M.exe
CreateProcess took 1127315 us (duration=2421768 ticks, freq=2148262 ticks/sec)
CreateProcess took 4621 us (duration=9928 ticks, freq=2148262 ticks/sec)
CreateProcess took 4358 us (duration=9363 ticks, freq=2148262 ticks/sec)
CreateProcess took 4261 us (duration=9154 ticks, freq=2148262 ticks/sec)
CreateProcess took 4569 us (duration=9816 ticks, freq=2148262 ticks/sec)
```
