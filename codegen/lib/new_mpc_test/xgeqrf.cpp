//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: xgeqrf.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:31:25
//

// Include Files
#include <cmath>
#include "rt_nonfinite.h"
#include <string.h>
#include "new_mpc_test.h"
#include "xgeqrf.h"
#include "xger.h"
#include "xgemv.h"

// Function Declarations
static double rt_hypotd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

//
// Arguments    : double A_data[]
//                int A_size[2]
//                double tau_data[]
//                int tau_size[1]
// Return Type  : void
//
void xgeqrf(double A_data[], int A_size[2], double tau_data[], int tau_size[1])
{
  int m;
  int n;
  int lastc;
  int mn;
  double work_data[2];
  int i;
  int i_i;
  int b_tmp;
  double atmp;
  double xnorm;
  int lastv;
  double beta1;
  int ia;
  int knt;
  int exitg1;
  m = A_size[0];
  n = A_size[1];
  lastc = A_size[0];
  mn = A_size[1];
  if (lastc < mn) {
    mn = lastc;
  }

  tau_size[0] = (signed char)mn;
  if ((A_size[0] != 0) && (A_size[1] != 0)) {
    lastc = (signed char)A_size[1];
    if (0 <= lastc - 1) {
      memset(&work_data[0], 0, (unsigned int)(lastc * (int)sizeof(double)));
    }

    for (i = 0; i < mn; i++) {
      i_i = i + i * m;
      b_tmp = (m - i) - 1;
      if (i + 1 < m) {
        atmp = A_data[i_i];
        lastc = i_i + 2;
        tau_data[0] = 0.0;
        if (1 + b_tmp > 0) {
          xnorm = 0.0;
          if (b_tmp >= 1) {
            xnorm = std::abs(A_data[i_i + 1]);
          }

          if (xnorm != 0.0) {
            beta1 = rt_hypotd_snf(A_data[i_i], xnorm);
            if (A_data[i_i] >= 0.0) {
              beta1 = -beta1;
            }

            if (std::abs(beta1) < 1.0020841800044864E-292) {
              knt = -1;
              ia = i_i + b_tmp;
              do {
                knt++;
                for (lastv = lastc; lastv <= ia + 1; lastv++) {
                  A_data[lastv - 1] *= 9.9792015476736E+291;
                }

                beta1 *= 9.9792015476736E+291;
                atmp *= 9.9792015476736E+291;
              } while (!(std::abs(beta1) >= 1.0020841800044864E-292));

              xnorm = 0.0;
              if (b_tmp >= 1) {
                xnorm = std::abs(A_data[i_i + 1]);
              }

              beta1 = rt_hypotd_snf(atmp, xnorm);
              if (atmp >= 0.0) {
                beta1 = -beta1;
              }

              tau_data[0] = (beta1 - atmp) / beta1;
              xnorm = 1.0 / (atmp - beta1);
              ia = i_i + b_tmp;
              for (lastv = lastc; lastv <= ia + 1; lastv++) {
                A_data[lastv - 1] *= xnorm;
              }

              for (lastv = 0; lastv <= knt; lastv++) {
                beta1 *= 1.0020841800044864E-292;
              }

              atmp = beta1;
            } else {
              tau_data[0] = (beta1 - A_data[i_i]) / beta1;
              xnorm = 1.0 / (A_data[i_i] - beta1);
              ia = i_i + b_tmp;
              for (lastv = lastc; lastv <= ia + 1; lastv++) {
                A_data[lastv - 1] *= xnorm;
              }

              atmp = beta1;
            }
          }
        }

        A_data[i_i] = atmp;
      } else {
        tau_data[i] = 0.0;
      }

      if (i + 1 < n) {
        atmp = A_data[i_i];
        A_data[i_i] = 1.0;
        if (tau_data[0] != 0.0) {
          lastv = 1 + b_tmp;
          lastc = i_i + b_tmp;
          while ((lastv > 0) && (A_data[lastc] == 0.0)) {
            lastv--;
            lastc--;
          }

          lastc = 1;
          ia = m;
          do {
            exitg1 = 0;
            if (ia + 1 <= m + lastv) {
              if (A_data[ia] != 0.0) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc = 0;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        } else {
          lastv = 0;
          lastc = 0;
        }

        if (lastv > 0) {
          xgemv(lastv, lastc, A_data, 1 + m, m, A_data, i_i + 1, work_data);
          xger(lastv, lastc, -tau_data[0], i_i + 1, work_data, A_data, 1 + m, m);
        }

        A_data[i_i] = atmp;
      }
    }
  }
}

//
// File trailer for xgeqrf.cpp
//
// [EOF]
//
