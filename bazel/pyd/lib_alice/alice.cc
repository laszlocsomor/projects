#include "python.h"

#if PY_MAJOR_VERSION >= 3
    #define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
#else
    #define MOD_INIT(name) PyMODINIT_FUNC init##name(void)
#endif

extern "C" {
  MOD_INIT(alice);
  __declspec(dllexport) PyObject* _qux_imp(PyObject*, PyObject*);
  __declspec(dllimport) int bar(int x);
}

static PyMethodDef _methods[] = {
  {"qux", _qux_imp, METH_O, "Some docstring for qux()."}, 
  {nullptr, nullptr},
};

static const char* _docstring = "Example module \"alice\" docstring.";

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef _moduledef = {
  PyModuleDef_HEAD_INIT, "alice", _docstring, 0, _methods, nullptr, nullptr,
  nullptr, nullptr,
};
#endif

MOD_INIT(alice) {
#if PY_MAJOR_VERSION >= 3
  return PyModule_Create(&_moduledef);
#else
  Py_InitModule3("alice", _methods, _docstring);
#endif
}

PyObject* _qux_imp(PyObject* module, PyObject* arg) {
  int v;
  if (!PyArg_Parse(arg, "i:qux", &v)) {
    return nullptr;
  }
  return Py_BuildValue("i", bar(v) * 10);
}
