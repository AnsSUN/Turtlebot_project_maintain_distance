//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: qr.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:31:25
//

// Include Files
#include <string.h>
#include "rt_nonfinite.h"
#include "new_mpc_test.h"
#include "qr.h"
#include "xger.h"
#include "xgemv.h"
#include "xgeqrf.h"

// Function Definitions

//
// Arguments    : const double A_data[]
//                const int A_size[2]
//                double Q_data[]
//                int Q_size[2]
//                double R_data[]
//                int R_size[2]
// Return Type  : void
//
void qr(const double A_data[], const int A_size[2], double Q_data[], int Q_size
        [2], double R_data[], int R_size[2])
{
  int m;
  int n;
  int b_A_size[2];
  int lastc;
  int iaii;
  int lastv;
  double b_A_data[4];
  double tau_data[2];
  int tau_size[1];
  int i;
  int ia;
  double work_data[2];
  int exitg1;
  m = A_size[0];
  n = A_size[1];
  Q_size[0] = (signed char)A_size[0];
  Q_size[1] = (signed char)A_size[0];
  R_size[0] = A_size[0];
  R_size[1] = A_size[1];
  if (A_size[0] > A_size[1]) {
    if ((0 <= A_size[1] - 1) && (0 <= A_size[0] - 1)) {
      memcpy(&Q_data[0], &A_data[0], (unsigned int)(A_size[0] * (int)sizeof
              (double)));
    }

    iaii = A_size[1] + 1;
    for (lastv = iaii; lastv <= m; lastv++) {
      for (i = 0; i < m; i++) {
        Q_data[i + Q_size[0] * (lastv - 1)] = 0.0;
      }
    }

    xgeqrf(Q_data, Q_size, tau_data, tau_size);
    if (0 <= A_size[1] - 1) {
      R_data[0] = Q_data[0];
      if (2 <= A_size[0]) {
        R_data[1] = 0.0;
      }
    }

    if (A_size[0] >= 1) {
      iaii = A_size[0] - 1;
      for (lastv = n; lastv <= iaii; lastv++) {
        ia = lastv * m;
        lastc = m - 1;
        if (0 <= lastc) {
          memset(&Q_data[ia], 0, (unsigned int)((((lastc + ia) - ia) + 1) * (int)
                  sizeof(double)));
        }

        Q_data[ia + lastv] = 1.0;
      }

      n = A_size[1] - 1;
      lastc = (signed char)Q_size[1];
      if (0 <= lastc - 1) {
        memset(&work_data[0], 0, (unsigned int)(lastc * (int)sizeof(double)));
      }

      for (i = A_size[1]; i >= 1; i--) {
        iaii = i + (i - 1) * m;
        if (i < m) {
          Q_data[iaii - 1] = 1.0;
          if (tau_data[n] != 0.0) {
            lastv = 2;
            lastc = iaii;
            while ((lastv > 0) && (Q_data[lastc] == 0.0)) {
              lastv--;
              lastc--;
            }

            lastc = 1;
            ia = iaii + 2;
            do {
              exitg1 = 0;
              if (ia <= (iaii + lastv) + 1) {
                if (Q_data[ia - 1] != 0.0) {
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
            xgemv(lastv, lastc, Q_data, iaii + 2, 2, Q_data, iaii, work_data);
            xger(lastv, lastc, -tau_data[n], iaii, work_data, Q_data, iaii + 2,
                 2);
          }

          lastc = iaii + 1;
          for (lastv = lastc; lastv <= lastc; lastv++) {
            Q_data[lastv - 1] *= -tau_data[n];
          }
        }

        Q_data[iaii - 1] = 1.0 - tau_data[n];
        if (0 <= i - 2) {
          Q_data[iaii - 2] = 0.0;
        }

        n--;
      }
    }
  } else {
    b_A_size[0] = A_size[0];
    b_A_size[1] = A_size[1];
    lastc = A_size[0] * A_size[1];
    if (0 <= lastc - 1) {
      memcpy(&b_A_data[0], &A_data[0], (unsigned int)(lastc * (int)sizeof(double)));
    }

    xgeqrf(b_A_data, b_A_size, tau_data, tau_size);
    for (lastv = 0; lastv < m; lastv++) {
      for (i = 0; i <= lastv; i++) {
        R_data[i + R_size[0] * lastv] = b_A_data[i + b_A_size[0] * lastv];
      }

      if (lastv + 2 <= m) {
        R_data[1 + R_size[0] * lastv] = 0.0;
      }
    }

    iaii = A_size[0] + 1;
    for (lastv = iaii; lastv <= n; lastv++) {
      for (i = 0; i < m; i++) {
        R_data[i + R_size[0] * (lastv - 1)] = b_A_data[i + b_A_size[0] * (lastv
          - 1)];
      }
    }

    if (A_size[0] >= 1) {
      iaii = A_size[0] - 1;
      for (lastv = m; lastv <= iaii; lastv++) {
        ia = lastv * m;
        lastc = m - 1;
        if (0 <= lastc) {
          memset(&b_A_data[ia], 0, (unsigned int)((((lastc + ia) - ia) + 1) *
                  (int)sizeof(double)));
        }

        b_A_data[ia + lastv] = 1.0;
      }

      n = A_size[0] - 1;
      lastc = (signed char)b_A_size[1];
      if (0 <= lastc - 1) {
        memset(&work_data[0], 0, (unsigned int)(lastc * (int)sizeof(double)));
      }

      for (i = A_size[0]; i >= 1; i--) {
        iaii = i + (i - 1) * m;
        if (i < m) {
          b_A_data[iaii - 1] = 1.0;
          if (tau_data[n] != 0.0) {
            lastv = 2;
            lastc = iaii;
            while ((lastv > 0) && (b_A_data[lastc] == 0.0)) {
              lastv--;
              lastc--;
            }

            lastc = 1;
            ia = iaii + 2;
            do {
              exitg1 = 0;
              if (ia <= (iaii + lastv) + 1) {
                if (b_A_data[ia - 1] != 0.0) {
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
            xgemv(lastv, lastc, b_A_data, iaii + 2, 2, b_A_data, iaii, work_data);
            xger(lastv, lastc, -tau_data[n], iaii, work_data, b_A_data, iaii + 2,
                 2);
          }

          lastc = iaii + 1;
          for (lastv = lastc; lastv <= lastc; lastv++) {
            b_A_data[lastv - 1] *= -tau_data[n];
          }
        }

        b_A_data[iaii - 1] = 1.0 - tau_data[n];
        if (0 <= i - 2) {
          b_A_data[iaii - 2] = 0.0;
        }

        n--;
      }
    }

    for (lastv = 0; lastv < m; lastv++) {
      for (i = 0; i < m; i++) {
        Q_data[i + Q_size[0] * lastv] = b_A_data[i + b_A_size[0] * lastv];
      }
    }
  }
}

//
// File trailer for qr.cpp
//
// [EOF]
//
