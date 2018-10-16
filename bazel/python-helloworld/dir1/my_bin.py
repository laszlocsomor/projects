from __future__ import print_function
from dir1.dir2 import my_lib
import sys
print("argc=%d, Foo(argc)=%d" % (len(sys.argv), my_lib.Foo(len(sys.argv))))
