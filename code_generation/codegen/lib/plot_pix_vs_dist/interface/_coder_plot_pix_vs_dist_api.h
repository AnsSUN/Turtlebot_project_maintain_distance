/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_plot_pix_vs_dist_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Oct-2019 20:46:56
 */

#ifndef _CODER_PLOT_PIX_VS_DIST_API_H
#define _CODER_PLOT_PIX_VS_DIST_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_plot_pix_vs_dist_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real_T plot_pix_vs_dist(real_T pixel_width);
extern void plot_pix_vs_dist_api(const mxArray * const prhs[1], int32_T nlhs,
  const mxArray *plhs[1]);
extern void plot_pix_vs_dist_atexit(void);
extern void plot_pix_vs_dist_initialize(void);
extern void plot_pix_vs_dist_terminate(void);
extern void plot_pix_vs_dist_xil_terminate(void);

#endif

/*
 * File trailer for _coder_plot_pix_vs_dist_api.h
 *
 * [EOF]
 */
