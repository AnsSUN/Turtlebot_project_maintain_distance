//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: lds_convert_types.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-Oct-2019 21:08:10
//
#ifndef LDS_CONVERT_TYPES_H
#define LDS_CONVERT_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

//
// File trailer for lds_convert_types.h
//
// [EOF]
//
