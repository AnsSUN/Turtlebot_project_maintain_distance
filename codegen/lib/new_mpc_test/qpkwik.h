//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: qpkwik.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:31:25
//
#ifndef QPKWIK_H
#define QPKWIK_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "new_mpc_test_types.h"

// Function Declarations
extern void qpkwik(const double Linv_data[], const int Linv_size[2], const
                   double Hinv_data[], const int Hinv_size[2], const double b[3],
                   double x_data[], int x_size[1], double lambda[3], double
                   *status, short iA[3]);

#endif

//
// File trailer for qpkwik.h
//
// [EOF]
//
