/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_lds_convert_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Oct-2019 21:08:10
 */

#ifndef _CODER_LDS_CONVERT_API_H
#define _CODER_LDS_CONVERT_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_lds_convert_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void lds_convert(emxArray_real_T *detect_rad, emxArray_real_T *x_y_coord);
extern void lds_convert_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1]);
extern void lds_convert_atexit(void);
extern void lds_convert_initialize(void);
extern void lds_convert_terminate(void);
extern void lds_convert_xil_terminate(void);

#endif

/*
 * File trailer for _coder_lds_convert_api.h
 *
 * [EOF]
 */
