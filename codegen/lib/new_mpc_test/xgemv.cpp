//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: xgemv.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:31:25
//

// Include Files
#include "rt_nonfinite.h"
#include "new_mpc_test.h"
#include "xgemv.h"

// Function Definitions

//
// Arguments    : int m
//                int n
//                const double A_data[]
//                int ia0
//                int lda
//                const double x_data[]
//                int ix0
//                double y_data[]
// Return Type  : void
//
void xgemv(int m, int n, const double A_data[], int ia0, int lda, const double
           x_data[], int ix0, double y_data[])
{
  int iy;
  int i8;
  int iac;
  int ix;
  double c;
  int i9;
  int ia;
  if (n != 0) {
    for (iy = 0; iy < n; iy++) {
      y_data[0] = 0.0;
    }

    iy = 0;
    i8 = ia0 + lda * (n - 1);
    for (iac = ia0; lda < 0 ? iac >= i8 : iac <= i8; iac += lda) {
      ix = ix0;
      c = 0.0;
      i9 = (iac + m) - 1;
      for (ia = iac; ia <= i9; ia++) {
        c += A_data[ia - 1] * x_data[ix - 1];
        ix++;
      }

      y_data[iy] += c;
      iy++;
    }
  }
}

//
// File trailer for xgemv.cpp
//
// [EOF]
//
