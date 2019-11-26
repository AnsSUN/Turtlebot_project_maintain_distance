/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_y_coord_estimation_vision_410X308_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Oct-2019 20:50:36
 */

#ifndef _CODER_Y_COORD_ESTIMATION_VISION_410X308_API_H
#define _CODER_Y_COORD_ESTIMATION_VISION_410X308_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_y_coord_estimation_vision_410X308_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real_T y_coord_estimation_vision_410X308(real_T pix_fromx, real_T
  x_rel_dist_vis);
extern void y_coord_estimation_vision_410X308_api(const mxArray * const prhs[2],
  int32_T nlhs, const mxArray *plhs[1]);
extern void y_coord_estimation_vision_410X308_atexit(void);
extern void y_coord_estimation_vision_410X308_initialize(void);
extern void y_coord_estimation_vision_410X308_terminate(void);
extern void y_coord_estimation_vision_410X308_xil_terminate(void);

#endif

/*
 * File trailer for _coder_y_coord_estimation_vision_410X308_api.h
 *
 * [EOF]
 */
