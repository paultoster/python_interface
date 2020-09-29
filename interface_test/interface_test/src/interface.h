#pragma once
#define PY_SSIZE_T_CLEAN

#ifdef _DEBUG
#define DEBUG_HOLD_SPEZIAL_BLABLA
#undef _DEBUG
#endif

#include "Python.h"

#ifdef DEBUG_HOLD_SPEZIAL_BLABLA
#define  _DEBUG
#endif

