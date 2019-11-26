//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: vel_est_kalman_filt.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:21:00
//

// Include Files
#include <cmath>
#include "vel_est_kalman_filt.h"

// Function Definitions

//
// copy this data A, B ,C to outside of this function and also Q, R, P0
// Arguments    : const double A[16]
//                const double C[8]
//                const float Q[16]
//                float R
//                float Pm[16]
//                float K[8]
// Return Type  : void
//
void vel_est_kalman_filt(const double A[16], const double C[8], const float Q[16],
  float R, float Pm[16], float K[8])
{
  int i;
  int i0;
  int i1;
  int S_tmp_tmp;
  double S_tmp[8];
  float S[4];
  int i2;
  float b_C[8];
  float r;
  float t;
  float y[4];
  int Pm_tmp;
  float b_K[16];
  float b_Pm[16];

  //  This code has referred from
  //  https://www.cs.cmu.edu/~cga/dynopt/kalman/kalman.html and
  //  https://statweb.stanford.edu/~candes/acm116/Handouts/Kalman.pdf
  //  for more info check it out.
  //  as we are having longitudinal autonomy, therefore taking simple state transition matrix!! 
  //  designing the Kalman filter
  //  measurement step
  for (i = 0; i < 1000; i++) {
    //  measurement step
    for (i0 = 0; i0 < 2; i0++) {
      for (i1 = 0; i1 < 4; i1++) {
        S_tmp_tmp = i0 + (i1 << 1);
        S_tmp[i1 + (i0 << 2)] = C[S_tmp_tmp];
        b_C[S_tmp_tmp] = 0.0F;
        i2 = i1 << 2;
        b_C[S_tmp_tmp] = (((float)C[i0] * Pm[i2] + (float)C[i0 + 2] * Pm[1 + i2])
                          + (float)C[i0 + 4] * Pm[2 + i2]) + (float)C[i0 + 6] *
          Pm[3 + i2];
      }
    }

    for (i0 = 0; i0 < 2; i0++) {
      for (i1 = 0; i1 < 2; i1++) {
        i2 = i1 << 2;
        S[i0 + (i1 << 1)] = (((b_C[i0] * (float)S_tmp[i2] + b_C[i0 + 2] * (float)
          S_tmp[1 + i2]) + b_C[i0 + 4] * (float)S_tmp[2 + i2]) + b_C[i0 + 6] *
                             (float)S_tmp[3 + i2]) + R;
      }
    }

    // K = Pm*C'*inv(S); % change this inverse thing to solve with solutions of linear equations. 
    //  changing to linear eq solution:
    if (std::abs(S[1]) > std::abs(S[0])) {
      r = S[0] / S[1];
      t = 1.0F / (r * S[3] - S[2]);
      y[0] = S[3] / S[1] * t;
      y[1] = -t;
      y[2] = -S[2] / S[1] * t;
      y[3] = r * t;
    } else {
      r = S[1] / S[0];
      t = 1.0F / (S[3] - r * S[2]);
      y[0] = S[3] / S[0] * t;
      y[1] = -r * t;
      y[2] = -S[2] / S[0] * t;
      y[3] = t;
    }

    //  as it is 1 D dividing it, but for matrix linsolve is the best to get the "K". 
    //  prediction step
    for (i0 = 0; i0 < 4; i0++) {
      for (i1 = 0; i1 < 2; i1++) {
        Pm_tmp = i1 << 2;
        S_tmp_tmp = i0 + Pm_tmp;
        b_C[S_tmp_tmp] = 0.0F;
        b_C[S_tmp_tmp] = ((Pm[i0] * (float)S_tmp[Pm_tmp] + Pm[i0 + 4] * (float)
                           S_tmp[1 + Pm_tmp]) + Pm[i0 + 8] * (float)S_tmp[2 +
                          Pm_tmp]) + Pm[i0 + 12] * (float)S_tmp[3 + Pm_tmp];
      }

      K[i0] = 0.0F;
      r = b_C[i0 + 4];
      K[i0] = b_C[i0] * y[0] + r * y[1];
      K[i0 + 4] = 0.0F;
      K[i0 + 4] = b_C[i0] * y[2] + r * y[3];
      for (i1 = 0; i1 < 4; i1++) {
        Pm_tmp = i0 + (i1 << 2);
        b_K[Pm_tmp] = 0.0F;
        i2 = i1 << 1;
        b_K[Pm_tmp] = K[i0] * (float)C[i2] + K[i0 + 4] * (float)C[1 + i2];
      }

      for (i1 = 0; i1 < 4; i1++) {
        i2 = i1 << 2;
        Pm_tmp = i0 + i2;
        b_Pm[Pm_tmp] = Pm[Pm_tmp] - (((b_K[i0] * Pm[i2] + b_K[i0 + 4] * Pm[1 +
          i2]) + b_K[i0 + 8] * Pm[2 + i2]) + b_K[i0 + 12] * Pm[3 + i2]);
      }
    }

    for (i0 = 0; i0 < 4; i0++) {
      for (i1 = 0; i1 < 4; i1++) {
        Pm_tmp = i1 << 2;
        S_tmp_tmp = i0 + Pm_tmp;
        b_K[S_tmp_tmp] = 0.0F;
        b_K[S_tmp_tmp] = (((float)A[i0] * b_Pm[Pm_tmp] + (float)A[i0 + 4] *
                           b_Pm[1 + Pm_tmp]) + (float)A[i0 + 8] * b_Pm[2 +
                          Pm_tmp]) + (float)A[i0 + 12] * b_Pm[3 + Pm_tmp];
      }

      for (i1 = 0; i1 < 4; i1++) {
        Pm_tmp = i0 + (i1 << 2);
        Pm[Pm_tmp] = (((b_K[i0] * (float)A[i1] + b_K[i0 + 4] * (float)A[i1 + 4])
                       + b_K[i0 + 8] * (float)A[i1 + 8]) + b_K[i0 + 12] * (float)
                      A[i1 + 12]) + Q[Pm_tmp];
      }
    }
  }
}

//
// File trailer for vel_est_kalman_filt.cpp
//
// [EOF]
//
