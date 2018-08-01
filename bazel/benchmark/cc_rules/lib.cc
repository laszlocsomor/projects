#define _C(a,b) a##b
#define C(a,b) _C(a,b)

extern "C" int C(foo, DEP1)(void);
extern "C" int C(foo, DEP2)(void);

extern "C" int C(foo, IVALUE)(void) {
  return C(foo, DEP1)() > C(foo, DEP2)() ? C(foo, DEP1)() : C(foo, DEP2)();
}
