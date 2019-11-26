//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: abs.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:31:25
//

// Include Files
#include <cmath>
#include "rt_nonfinite.h"
#include "new_mpc_test.h"
#include "abs.h"

// Function Definitions

//
// Arguments    : const double x[2]
//                double y[2]
// Return Type  : void
//
void b_abs(const double x[2], double y[2])
{
  y[0] = std::abs(x[0]);
  y[1] = std::abs(x[1]);
}

//
// Arguments    : const double x[3]
//                double y[3]
// Return Type  : void
//
void c_abs(const double x[3], double y[3])
{
  y[0] = std::abs(x[0]);
  y[1] = std::abs(x[1]);
  y[2] = std::abs(x[2]);
}

//
// File trailer for abs.cpp
//
// [EOF]
//
