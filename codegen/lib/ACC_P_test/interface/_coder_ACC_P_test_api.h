/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_ACC_P_test_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Oct-2019 17:25:40
 */

#ifndef _CODER_ACC_P_TEST_API_H
#define _CODER_ACC_P_TEST_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_ACC_P_test_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real32_T ACC_P_test(real32_T rel_velx, real32_T rel_vely, real32_T
  rel_posx, real32_T rel_posy, real_T vel_egox, real_T vel_egoy);
extern void ACC_P_test_api(const mxArray * const prhs[6], int32_T nlhs, const
  mxArray *plhs[1]);
extern void ACC_P_test_atexit(void);
extern void ACC_P_test_initialize(void);
extern void ACC_P_test_terminate(void);
extern void ACC_P_test_xil_terminate(void);

#endif

/*
 * File trailer for _coder_ACC_P_test_api.h
 *
 * [EOF]
 */
