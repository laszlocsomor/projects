#!/usr/bin/python
from __future__ import print_function
import os
import sys

if len(sys.argv) != 2:
  print("Usage: $0 <input>", file=sys.stderr)
  sys.exit(1)

with open(sys.argv[1], "rt") as f:
  data = [int(line.strip()) for line in f.readlines()]

def percentile_index(total, a, b):
  return min(total - 1, (total * a) // b)

i = 1
deltas = []
while i < len(data):
  deltas.append(data[i] - data[i-1])
  i += 1

deltas = sorted(deltas)
print("Bash commands (sample size is %d):" % len(deltas))
print("  95th %%: %d us" % deltas[percentile_index(len(deltas) - 1, 95, 100)])
print("  99th %%: %d us" % deltas[percentile_index(len(deltas) - 1, 99, 100)])
print("  99.5th %%: %d us" % deltas[percentile_index(len(deltas) - 1, 995, 1000)])
print("  99.9th %%: %d us" % deltas[percentile_index(len(deltas) - 1, 999, 1000)])
print("  max: %d us" % deltas[-1])
