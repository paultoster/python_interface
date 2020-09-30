#pragma once
#define PY_SSIZE_T_CLEAN

#ifdef _DEBUG
#define DEBUG_HOLD_SPEZIAL_BLABLA
#undef _DEBUG
#endif

#include "Python.h"

#define TYPE_NONE  0
#define TYPE_INIT  1
#define TYPE_FIRST 2
#define TYPE_RUN   2

#define IAVALUE 0
#define IBVALUE 1
#define ICVALUE 2
#define IDVALUE 3
#define NVALUE  4
struct SInput
{
  int type;
  double values[NVALUE];
};
extern struct SInput input;
struct SOutput
{
  int type;
  double avalue;
  double bvalue;
  double cvalue;
  double dvalue;
};
extern struct SOutput output;

#ifdef DEBUG_HOLD_SPEZIAL_BLABLA
#define  _DEBUG
#endif

