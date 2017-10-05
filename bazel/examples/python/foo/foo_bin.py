from examples.python.foo.bar import bar_lib

def Main():
  print("Hello!")
  print(bar_lib.BarFunc(21))


if __name__ == '__main__':
  Main()
