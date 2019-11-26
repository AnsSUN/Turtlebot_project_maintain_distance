//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: xger.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:31:25
//

// Include Files
#include "rt_nonfinite.h"
#include "new_mpc_test.h"
#include "xger.h"

// Function Definitions

//
// Arguments    : int m
//                int n
//                double alpha1
//                int ix0
//                const double y_data[]
//                double A_data[]
//                int ia0
//                int lda
// Return Type  : void
//
void xger(int m, int n, double alpha1, int ix0, const double y_data[], double
          A_data[], int ia0, int lda)
{
  int jA;
  int jy;
  int j;
  double temp;
  int ix;
  int i10;
  int i11;
  int ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 0; j < n; j++) {
      if (y_data[jy] != 0.0) {
        temp = y_data[jy] * alpha1;
        ix = ix0;
        i10 = jA + 1;
        i11 = m + jA;
        for (ijA = i10; ijA <= i11; ijA++) {
          A_data[ijA - 1] += A_data[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += lda;
    }
  }
}

//
// File trailer for xger.cpp
//
// [EOF]
//
