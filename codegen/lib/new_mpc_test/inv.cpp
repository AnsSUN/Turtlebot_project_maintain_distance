//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: inv.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:31:25
//

// Include Files
#include <cmath>
#include <string.h>
#include "rt_nonfinite.h"
#include "new_mpc_test.h"
#include "inv.h"

// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[2]
//                double y_data[]
//                int y_size[2]
// Return Type  : void
//
void inv(const double x_data[], const int x_size[2], double y_data[], int
         y_size[2])
{
  int n;
  int iy;
  double b_x_data[4];
  int ipiv_data[2];
  int yk;
  int k;
  int i0;
  int j;
  int p_data[2];
  int i;
  int ix;
  double temp;
  int i1;
  int ijA;
  if ((x_size[0] == 0) || (x_size[1] == 0)) {
    y_size[0] = x_size[0];
    y_size[1] = x_size[1];
    iy = x_size[0] * x_size[1];
    if (0 <= iy - 1) {
      memcpy(&y_data[0], &x_data[0], (unsigned int)(iy * (int)sizeof(double)));
    }
  } else {
    n = x_size[0];
    y_size[0] = x_size[0];
    y_size[1] = x_size[1];
    iy = x_size[0] * x_size[1];
    if (0 <= iy - 1) {
      memset(&y_data[0], 0, (unsigned int)(iy * (int)sizeof(double)));
      memcpy(&b_x_data[0], &x_data[0], (unsigned int)(iy * (int)sizeof(double)));
    }

    iy = x_size[0];
    ipiv_data[0] = 1;
    yk = 1;
    for (k = 2; k <= iy; k++) {
      yk++;
      ipiv_data[1] = yk;
    }

    i0 = x_size[0];
    for (j = 0; j <= i0 - 2; j++) {
      iy = 0;
      if ((n > 1) && (std::abs(b_x_data[1]) > std::abs(b_x_data[0]))) {
        iy = 1;
      }

      if (b_x_data[iy] != 0.0) {
        if (iy != 0) {
          ipiv_data[0] = 2;
          ix = 0;
          iy = 1;
          for (k = 0; k < n; k++) {
            temp = b_x_data[ix];
            b_x_data[ix] = b_x_data[iy];
            b_x_data[iy] = temp;
            ix += n;
            iy += n;
          }
        }

        for (i = 2; i <= n; i++) {
          b_x_data[1] /= b_x_data[0];
        }
      }

      yk = n;
      iy = x_size[0] + 1;
      for (i = 0; i <= n - 2; i++) {
        temp = b_x_data[yk];
        if (b_x_data[yk] != 0.0) {
          ix = 1;
          k = iy + 1;
          i1 = (n + iy) - 1;
          for (ijA = k; ijA <= i1; ijA++) {
            b_x_data[ijA - 1] += b_x_data[ix] * -temp;
            ix++;
          }
        }

        yk += n;
        iy += n;
      }
    }

    iy = x_size[0];
    p_data[0] = 1;
    yk = 1;
    for (k = 2; k <= iy; k++) {
      yk++;
      p_data[1] = yk;
    }

    i0 = x_size[0];
    for (k = 0; k < i0; k++) {
      if (ipiv_data[k] > 1 + k) {
        iy = p_data[1];
        p_data[1] = p_data[k];
        p_data[k] = iy;
      }
    }

    for (k = 0; k < n; k++) {
      yk = y_size[0] * (p_data[k] - 1);
      y_data[k + yk] = 1.0;
      for (j = k + 1; j <= n; j++) {
        if (y_data[(j + yk) - 1] != 0.0) {
          i0 = j + 1;
          for (i = i0; i <= n; i++) {
            iy = 1 + yk;
            y_data[iy] -= y_data[(j + y_size[0] * (p_data[k] - 1)) - 1] *
              b_x_data[1 + x_size[0] * (j - 1)];
          }
        }
      }
    }

    for (j = 0; j < n; j++) {
      yk = n * j - 1;
      for (k = n; k >= 1; k--) {
        iy = n * (k - 1);
        i0 = k + yk;
        if (y_data[i0] != 0.0) {
          y_data[i0] /= b_x_data[(k + iy) - 1];
          for (i = 0; i <= k - 2; i++) {
            y_data[yk + 1] -= y_data[i0] * b_x_data[iy];
          }
        }
      }
    }
  }
}

//
// File trailer for inv.cpp
//
// [EOF]
//
