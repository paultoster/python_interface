#include "interface.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string>

static PyObject *InterfaceError;

static PyObject *
interface_system(PyObject *self, PyObject *args)
{
  const char *command;
  int sts;

  if (PyArg_ParseTuple(args, "s", &command))
  {
    sts = system(command);
    return PyLong_FromLong(sts);
  }

  return NULL;
}

static PyObject *
interface_values(PyObject *self, PyObject *args)
{
  double d1, d2, d3;
  std::string string;
  int iokay = 1;
  PyObject *ret;

  if (PyArg_ParseTuple(args, "ddd", &d1, &d2, &d3))
  {
    d1 += 10.;
    d2 += 100.;
    d3 += 100.;

    /* Build the output tuple */
    ret = Py_BuildValue("iddd", iokay, d1, d2, d3);
    return ret;

  }
  else
  {
    d1 = 0.;
    d2 = 0.;
    d3 = 0.;
    iokay = 0;
  }
  ret = Py_BuildValue("iddd", iokay, d1, d2, d3);
  return ret;
}

static PyObject *
interface_str(PyObject *self, PyObject *args)
{
  char *str;
  std::string string;
  int ierr = 0;

  if (PyArg_ParseTuple(args, "s", &str))
  {
    string = std::string(str);
    return PyLong_FromLong(ierr);

  }
  ierr = 1;
  return PyLong_FromLong(ierr);
}
static PyObject *
interface_dict(PyObject *self, PyObject *args)
{
  int ierr = 0;
  PyObject* pDict;
  if (PyArg_ParseTuple(args, "O!", &PyDict_Type, &pDict))
  {
    assert(PyDict_Check(pDict));
    double dvalue;

    PyObject *pItem = PyDict_GetItemString(pDict, "dvalue");
    if (PyFloat_Check(pItem))
    {
      dvalue = PyFloat_AsDouble(pItem);
      PySys_WriteStdout("dvalue = %f", dvalue);
    }


    return PyLong_FromLong(ierr);
  }
  else
  {
    ierr = 1;
    return PyLong_FromLong(ierr);
  }

  ierr = 1;
  return PyLong_FromLong(ierr);
}

PyMethodDef InterfaceMethods[] =
{


  { "setgetval",  interface_values, METH_VARARGS, "Execute 3 doubles, get 2 doubles." },
  { "getstr",     interface_str,    METH_VARARGS, "Execute a string." },
  { "getdict",    interface_dict,   METH_VARARGS, "Execute a dict." },
  { "system",     interface_system, METH_VARARGS, "Execute a shell command." },
  { NULL, NULL, 0, NULL }        /* Sentinel */
};

char *interface_doc = "Documentation";

static struct PyModuleDef interfacemodule = {
  PyModuleDef_HEAD_INIT,
  "interface",             /* name of module */
  interface_doc,           /* module documentation, may be NULL */
  -1,                      /* size of per-interpreter state of the module,
                              or -1 if the module keeps state in global variables. */
  InterfaceMethods
};

PyMODINIT_FUNC
PyInit_interface(void)
{
  PyObject *m;

  m = PyModule_Create(&interfacemodule);
  if (m == NULL)
    return NULL;

  InterfaceError = PyErr_NewException("interface.error", NULL, NULL);
  Py_INCREF(InterfaceError);
  PyModule_AddObject(m, "error", InterfaceError);
  return m;
}


