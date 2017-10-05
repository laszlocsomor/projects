import os

from examples.python.foo.bar import bar_lib

def Rlocation(runfile_path):
  with open(GetEnv('RUNFILES_MANIFEST_FILE'), 'r') as f:
    for l in f:
      tokens = l.strip().split(' ')
      if len(tokens) == 2:
        if runfile_path == tokens[0]:
          return tokens[1]
  raise Error("could not find runfile '%s'" % runfile_path)

def Main():
  print("Hello!")
  print(bar_lib.BarFunc(21))
  datafile = Rlocation('laszlocsomor/examples/python/foo/foo-data.txt')
  with open(datafile, 'r') as f:
    for line in f:
      print("data: " + line.strip())

if __name__ == '__main__':
  Main()
