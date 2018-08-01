#define _C(a,b) a##b
#define C(a,b) _C(a,b)

extern "C" int C(foo, IVALUE)(void) {
  return IVALUE;
}
