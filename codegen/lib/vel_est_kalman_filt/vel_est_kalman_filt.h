//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: vel_est_kalman_filt.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:21:00
//
#ifndef VEL_EST_KALMAN_FILT_H
#define VEL_EST_KALMAN_FILT_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "vel_est_kalman_filt_types.h"

// Function Declarations
extern void vel_est_kalman_filt(const double A[16], const double C[8], const
  float Q[16], float R, float Pm[16], float K[8]);

#endif

//
// File trailer for vel_est_kalman_filt.h
//
// [EOF]
//
