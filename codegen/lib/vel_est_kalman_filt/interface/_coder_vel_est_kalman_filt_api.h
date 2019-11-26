/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_vel_est_kalman_filt_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Oct-2019 17:21:00
 */

#ifndef _CODER_VEL_EST_KALMAN_FILT_API_H
#define _CODER_VEL_EST_KALMAN_FILT_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_vel_est_kalman_filt_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void vel_est_kalman_filt(real_T A[16], real_T C[8], real32_T Q[16],
  real32_T R, real32_T Pm[16], real32_T K[8]);
extern void vel_est_kalman_filt_api(const mxArray * const prhs[5], int32_T nlhs,
  const mxArray *plhs[1]);
extern void vel_est_kalman_filt_atexit(void);
extern void vel_est_kalman_filt_initialize(void);
extern void vel_est_kalman_filt_terminate(void);
extern void vel_est_kalman_filt_xil_terminate(void);

#endif

/*
 * File trailer for _coder_vel_est_kalman_filt_api.h
 *
 * [EOF]
 */
