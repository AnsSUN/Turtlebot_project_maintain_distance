/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_y_coord_estimation_vision_410X308_mex.cpp
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Oct-2019 20:50:36
 */

/* Include Files */
#include "_coder_y_coord_estimation_vision_410X308_api.h"
#include "_coder_y_coord_estimation_vision_410X308_mex.h"

/* Function Declarations */
static void c_y_coord_estimation_vision_410(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[2]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[2]
 * Return Type  : void
 */
static void c_y_coord_estimation_vision_410(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[2])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        33, "y_coord_estimation_vision_410X308");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 33,
                        "y_coord_estimation_vision_410X308");
  }

  /* Call the function. */
  y_coord_estimation_vision_410X308_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray * const plhs[]
 *                int32_T nrhs
 *                const mxArray * const prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(y_coord_estimation_vision_410X308_atexit);

  /* Module initialization. */
  y_coord_estimation_vision_410X308_initialize();

  /* Dispatch the entry-point. */
  c_y_coord_estimation_vision_410(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  y_coord_estimation_vision_410X308_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_y_coord_estimation_vision_410X308_mex.cpp
 *
 * [EOF]
 */
