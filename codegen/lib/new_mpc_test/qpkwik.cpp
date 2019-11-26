//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: qpkwik.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:31:25
//

// Include Files
#include <cmath>
#include <string.h>
#include "rt_nonfinite.h"
#include "new_mpc_test.h"
#include "qpkwik.h"
#include "qr.h"
#include "abs.h"
#include "norm.h"

// Variable Definitions
static const double dv0[6] = { 0.0, 0.0, 1.0, 1.0, -1.0, 0.4 };

// Function Declarations
static void DropConstraint(short kDrop, short iA[3], short *nA, short iC[3]);
static double KWIKfactor(const short iC[3], short nA, const double Linv_data[],
  const int Linv_size[2], double RLinv_data[], int RLinv_size[2], double D_data[],
  int D_size[2], double H_data[], int H_size[2]);
static void ResetToColdStart(short iA[3], short iC[3]);
static void Unconstrained(const double Hinv_data[], const int Hinv_size[2],
  double x_data[]);

// Function Definitions

//
// Arguments    : short kDrop
//                short iA[3]
//                short *nA
//                short iC[3]
// Return Type  : void
//
static void DropConstraint(short kDrop, short iA[3], short *nA, short iC[3])
{
  int i12;
  short i13;
  short i;
  iA[iC[kDrop - 1] - 1] = 0;
  if (kDrop < *nA) {
    i12 = *nA - 1;
    if (i12 < -32768) {
      i12 = -32768;
    }

    i13 = (short)i12;
    for (i = kDrop; i <= i13; i++) {
      iC[i - 1] = iC[i];
    }
  }

  iC[*nA - 1] = 0;
  i12 = *nA - 1;
  if (i12 < -32768) {
    i12 = -32768;
  }

  *nA = (short)i12;
}

//
// Arguments    : const short iC[3]
//                short nA
//                const double Linv_data[]
//                const int Linv_size[2]
//                double RLinv_data[]
//                int RLinv_size[2]
//                double D_data[]
//                int D_size[2]
//                double H_data[]
//                int H_size[2]
// Return Type  : double
//
static double KWIKfactor(const short iC[3], short nA, const double Linv_data[],
  const int Linv_size[2], double RLinv_data[], int RLinv_size[2], double D_data[],
  int D_size[2], double H_data[], int H_size[2])
{
  double Status;
  int TL_size_idx_0;
  int aoffset;
  int loop_ub;
  int i4;
  int i5;
  int i;
  double QQ_data[4];
  int QQ_size[2];
  double RR_data[4];
  int RR_size[2];
  double b[2];
  int exitg1;
  int i6;
  int b_size_idx_0;
  double b_data[2];
  double a_data[2];
  int b_i;
  double a;
  double TL_data[4];
  short j;
  short k;
  short i7;
  TL_size_idx_0 = Linv_size[0];
  Status = 1.0;
  aoffset = RLinv_size[0];
  loop_ub = RLinv_size[1];
  for (i4 = 0; i4 < loop_ub; i4++) {
    for (i5 = 0; i5 < aoffset; i5++) {
      RLinv_data[i5 + RLinv_size[0] * i4] = 0.0;
    }
  }

  i4 = nA;
  for (i = 0; i < i4; i++) {
    b[0] = dv0[iC[i] - 1];
    b[1] = dv0[iC[i] + 2];
    i5 = Linv_size[1];
    if (Linv_size[1] == 1) {
      aoffset = Linv_size[0];
      b_size_idx_0 = Linv_size[0];
      for (i5 = 0; i5 < aoffset; i5++) {
        b_data[i5] = 0.0;
        for (i6 = 0; i6 < 1; i6++) {
          b_data[i5] += Linv_data[i5] * b[0];
        }
      }
    } else {
      i6 = Linv_size[0];
      b_size_idx_0 = Linv_size[0];
      if (0 <= Linv_size[0] - 1) {
        memset(&b_data[0], 0, (unsigned int)(Linv_size[0] * (int)sizeof(double)));
      }

      for (loop_ub = 0; loop_ub < i5; loop_ub++) {
        aoffset = loop_ub * i6;
        for (b_i = 0; b_i < i6; b_i++) {
          b_data[b_i] += b[loop_ub] * Linv_data[aoffset + b_i];
        }
      }
    }

    for (i5 = 0; i5 < b_size_idx_0; i5++) {
      RLinv_data[i5 + RLinv_size[0] * i] = b_data[i5];
    }
  }

  qr(RLinv_data, RLinv_size, QQ_data, QQ_size, RR_data, RR_size);
  i = 0;
  do {
    exitg1 = 0;
    if (i <= nA - 1) {
      if (std::abs(RR_data[i + RR_size[0] * i]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      aoffset = Linv_size[0];
      loop_ub = QQ_size[0];
      for (i4 = 0; i4 < aoffset; i4++) {
        a_data[i4] = Linv_data[i4];
      }

      for (i4 = 0; i4 < loop_ub; i4++) {
        b_data[i4] = QQ_data[i4];
      }

      if ((Linv_size[0] == 1) || (QQ_size[0] == 1)) {
        a = 0.0;
        for (i4 = 0; i4 < aoffset; i4++) {
          a += a_data[i4] * b_data[i4];
        }

        TL_data[0] = a;
      } else {
        a = 0.0;
        for (i4 = 0; i4 < aoffset; i4++) {
          a += a_data[i4] * b_data[i4];
        }

        TL_data[0] = a;
      }

      for (i4 = 0; i4 < loop_ub; i4++) {
        b_data[i4] = QQ_data[i4 + QQ_size[0]];
      }

      if ((Linv_size[0] == 1) || (QQ_size[0] == 1)) {
        a = 0.0;
        for (i4 = 0; i4 < aoffset; i4++) {
          a += a_data[i4] * b_data[i4];
        }

        TL_data[TL_size_idx_0] = a;
      } else {
        a = 0.0;
        for (i4 = 0; i4 < aoffset; i4++) {
          a += a_data[i4] * b_data[i4];
        }

        TL_data[TL_size_idx_0] = a;
      }

      for (i4 = 0; i4 < aoffset; i4++) {
        a_data[i4] = Linv_data[i4 + Linv_size[0]];
      }

      for (i4 = 0; i4 < loop_ub; i4++) {
        b_data[i4] = QQ_data[i4];
      }

      if ((Linv_size[0] == 1) || (QQ_size[0] == 1)) {
        a = 0.0;
        for (i4 = 0; i4 < aoffset; i4++) {
          a += a_data[i4] * b_data[i4];
        }

        TL_data[1] = a;
      } else {
        a = 0.0;
        for (i4 = 0; i4 < aoffset; i4++) {
          a += a_data[i4] * b_data[i4];
        }

        TL_data[1] = a;
      }

      for (i4 = 0; i4 < loop_ub; i4++) {
        b_data[i4] = QQ_data[i4 + QQ_size[0]];
      }

      if ((Linv_size[0] == 1) || (QQ_size[0] == 1)) {
        a = 0.0;
        for (i4 = 0; i4 < aoffset; i4++) {
          a += a_data[i4] * b_data[i4];
        }

        TL_data[TL_size_idx_0 + 1] = a;
      } else {
        a = 0.0;
        for (i4 = 0; i4 < aoffset; i4++) {
          a += a_data[i4] * b_data[i4];
        }

        TL_data[TL_size_idx_0 + 1] = a;
      }

      aoffset = RLinv_size[0];
      loop_ub = RLinv_size[1];
      for (i4 = 0; i4 < loop_ub; i4++) {
        for (i5 = 0; i5 < aoffset; i5++) {
          RLinv_data[i5 + RLinv_size[0] * i4] = 0.0;
        }
      }

      for (j = nA; j >= 1; j--) {
        i4 = j - 1;
        RLinv_data[(j + RLinv_size[0] * i4) - 1] = 1.0;
        for (k = j; k <= nA; k++) {
          i5 = (j + RLinv_size[0] * (k - 1)) - 1;
          RLinv_data[i5] /= RR_data[(j + RR_size[0] * i4) - 1];
        }

        if (j > 1) {
          for (k = 2; k <= nA; k++) {
            RLinv_data[RLinv_size[0]] -= RR_data[RR_size[0]] * RLinv_data[1 +
              RLinv_size[0]];
          }
        }
      }

      for (j = 1; j < 3; j++) {
        i4 = j - 1;
        i5 = H_size[0] * i4;
        H_data[i5] = 0.0;
        i6 = nA + 1;
        if (i6 > 32767) {
          i6 = 32767;
        }

        i7 = (short)i6;
        for (k = i7; k < 3; k++) {
          H_data[i5] -= TL_data[TL_size_idx_0] * TL_data[(j + TL_size_idx_0) - 1];
        }

        H_data[i4] = H_data[i5];
      }

      for (j = 2; j < 3; j++) {
        H_data[H_size[0] + 1] = 0.0;
        i4 = nA + 1;
        if (i4 > 32767) {
          i4 = 32767;
        }

        i7 = (short)i4;
        for (k = i7; k < 3; k++) {
          a = TL_data[TL_size_idx_0 + 1];
          H_data[H_size[0] + 1] -= a * a;
        }
      }

      i4 = nA;
      for (loop_ub = 0; loop_ub < i4; loop_ub++) {
        j = (short)(1 + loop_ub);
        i5 = D_size[0] * loop_ub;
        D_data[i5] = 0.0;
        for (k = j; k <= nA; k++) {
          i6 = k - 1;
          D_data[i5] += TL_data[TL_size_idx_0 * i6] * RLinv_data[loop_ub +
            RLinv_size[0] * i6];
        }

        i5++;
        D_data[i5] = 0.0;
        for (k = j; k <= nA; k++) {
          D_data[i5] += TL_data[TL_size_idx_0 * (k - 1) + 1] *
            RLinv_data[loop_ub + RLinv_size[0] * (k - 1)];
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

//
// Arguments    : short iA[3]
//                short iC[3]
// Return Type  : void
//
static void ResetToColdStart(short iA[3], short iC[3])
{
  iA[0] = 0;
  iA[1] = 0;
  iC[1] = 0;
  iC[2] = 0;
  iA[2] = 1;
  iC[0] = 3;
}

//
// Arguments    : const double Hinv_data[]
//                const int Hinv_size[2]
//                double x_data[]
// Return Type  : void
//
static void Unconstrained(const double Hinv_data[], const int Hinv_size[2],
  double x_data[])
{
  x_data[0] = -Hinv_data[0] * -0.8 + -Hinv_data[Hinv_size[0]] * 0.0;
  x_data[1] = -Hinv_data[1] * -0.8 + -Hinv_data[Hinv_size[0] + 1] * 0.0;
}

//
// Arguments    : const double Linv_data[]
//                const int Linv_size[2]
//                const double Hinv_data[]
//                const int Hinv_size[2]
//                const double b[3]
//                double x_data[]
//                int x_size[1]
//                double lambda[3]
//                double *status
//                short iA[3]
// Return Type  : void
//
void qpkwik(const double Linv_data[], const int Linv_size[2], const double
            Hinv_data[], const int Hinv_size[2], const double b[3], double
            x_data[], int x_size[1], double lambda[3], double *status, short iA
            [3])
{
  double r_data[2];
  double rMin;
  int RLinv_size[2];
  int D_size[2];
  int H_size[2];
  int U_size_idx_0;
  boolean_T cTolComputed;
  double cTol[3];
  short iC[3];
  short nA;
  double Opt_data[4];
  double Rhs_data[4];
  boolean_T ColdReset;
  int exitg3;
  double lambdamin;
  double RLinv_data[4];
  double D_data[4];
  double H_data[4];
  int i2;
  int m;
  int aoffset;
  short kDrop;
  double Xnorm0;
  int i3;
  double z_data[2];
  int exitg2;
  double cMin;
  short i;
  short kNext;
  double a_data[2];
  int inner;
  double U_data[4];
  double AcRow[2];
  int k;
  int exitg1;
  boolean_T guard1 = false;
  double varargin_1[3];
  int b_i;
  double t1;
  boolean_T isT1Inf;
  boolean_T exitg4;
  *status = 1.0;
  iA[0] = 0;
  lambda[0] = 0.0;
  iA[1] = 0;
  lambda[1] = 0.0;
  iA[2] = 1;
  lambda[2] = 0.0;
  x_size[0] = 2;
  x_data[0] = 0.0;
  r_data[0] = 0.0;
  x_data[1] = 0.0;
  r_data[1] = 0.0;
  rMin = 0.0;
  RLinv_size[0] = Linv_size[0];
  RLinv_size[1] = Linv_size[1];
  D_size[0] = Linv_size[0];
  D_size[1] = Linv_size[1];
  H_size[0] = Linv_size[0];
  H_size[1] = Linv_size[1];
  U_size_idx_0 = Linv_size[0];
  cTolComputed = false;
  cTol[0] = 1.0;
  cTol[1] = 1.0;
  iC[1] = 0;
  iC[2] = 0;
  nA = 1;
  iC[0] = 3;
  Opt_data[2] = 0.0;
  Opt_data[3] = 0.0;
  Rhs_data[0] = -0.8;
  Rhs_data[2] = 0.0;
  Rhs_data[1] = 0.0;
  Rhs_data[3] = 0.0;
  ColdReset = false;
  do {
    exitg3 = 0;
    if ((nA > 0) && (*status <= 200.0)) {
      lambdamin = KWIKfactor(iC, nA, Linv_data, Linv_size, RLinv_data,
        RLinv_size, D_data, D_size, H_data, H_size);
      if (lambdamin < 0.0) {
        if (ColdReset) {
          *status = -2.0;
          exitg3 = 1;
        } else {
          iA[0] = 0;
          iA[1] = 0;
          iC[1] = 0;
          iC[2] = 0;
          iA[2] = 1;
          iC[0] = 3;
          nA = 1;
          ColdReset = true;
        }
      } else {
        i2 = nA;
        for (m = 0; m < i2; m++) {
          kDrop = (short)(1 + m);
          i3 = m + 3;
          if (i3 > 32767) {
            i3 = 32767;
          }

          Rhs_data[i3 - 1] = b[iC[m] - 1];
          for (i = kDrop; i <= nA; i++) {
            inner = (i + U_size_idx_0 * m) - 1;
            U_data[inner] = 0.0;
            i3 = nA;
            for (k = 0; k < i3; k++) {
              aoffset = RLinv_size[0] * k;
              U_data[inner] += RLinv_data[(i + aoffset) - 1] * RLinv_data[m +
                aoffset];
            }

            U_data[m + U_size_idx_0 * (i - 1)] = U_data[inner];
          }
        }

        aoffset = H_size[1];
        i2 = nA;
        z_data[0] = -0.8;
        z_data[1] = 0.0;
        m = H_size[1];
        for (i3 = 0; i3 < aoffset; i3++) {
          a_data[i3] = H_data[H_size[0] * i3];
        }

        if (H_size[1] == 1) {
          lambdamin = 0.0;
          for (i3 = 0; i3 < m; i3++) {
            lambdamin += a_data[i3] * z_data[i3];
          }

          Opt_data[0] = lambdamin;
        } else {
          lambdamin = 0.0;
          for (i3 = 0; i3 < m; i3++) {
            lambdamin += a_data[i3] * z_data[i3];
          }

          Opt_data[0] = lambdamin;
        }

        for (k = 0; k < i2; k++) {
          i3 = k + 3;
          if (i3 > 32767) {
            i3 = 32767;
          }

          Opt_data[0] += D_data[D_size[0] * k] * Rhs_data[i3 - 1];
        }

        for (i3 = 0; i3 < aoffset; i3++) {
          a_data[i3] = H_data[H_size[0] * i3 + 1];
        }

        if (H_size[1] == 1) {
          lambdamin = 0.0;
          for (i3 = 0; i3 < m; i3++) {
            lambdamin += a_data[i3] * z_data[i3];
          }

          Opt_data[1] = lambdamin;
        } else {
          lambdamin = 0.0;
          for (i3 = 0; i3 < m; i3++) {
            lambdamin += a_data[i3] * z_data[i3];
          }

          Opt_data[1] = lambdamin;
        }

        for (k = 0; k < i2; k++) {
          i3 = k + 3;
          if (i3 > 32767) {
            i3 = 32767;
          }

          Opt_data[1] += D_data[D_size[0] * k + 1] * Rhs_data[i3 - 1];
        }

        i2 = nA;
        m = D_size[0];
        aoffset = D_size[0];
        i3 = nA;
        z_data[0] = -0.8;
        z_data[1] = 0.0;
        for (b_i = 0; b_i < i2; b_i++) {
          for (inner = 0; inner < aoffset; inner++) {
            a_data[inner] = D_data[inner + D_size[0] * b_i];
          }

          if (m == 1) {
            lambdamin = 0.0;
            for (inner = 0; inner < 1; inner++) {
              lambdamin += a_data[0] * -0.8;
            }

            Opt_data[b_i + 2] = lambdamin;
          } else {
            lambdamin = 0.0;
            for (inner = 0; inner < m; inner++) {
              lambdamin += a_data[inner] * z_data[inner];
            }

            Opt_data[b_i + 2] = lambdamin;
          }

          for (k = 0; k < i3; k++) {
            inner = k + 3;
            if (inner > 32767) {
              inner = 32767;
            }

            Opt_data[b_i + 2] += U_data[b_i + U_size_idx_0 * k] * Rhs_data[inner
              - 1];
          }
        }

        lambdamin = -1.0E-12;
        kDrop = 0;
        i2 = nA;
        for (b_i = 0; b_i < i2; b_i++) {
          i3 = b_i + 3;
          if (i3 > 32767) {
            i3 = 32767;
          }

          lambda[iC[b_i] - 1] = Opt_data[i3 - 1];
          i3 = b_i + 3;
          if (i3 > 32767) {
            i3 = 32767;
          }

          if ((Opt_data[i3 - 1] < lambdamin) && (1 + b_i <= nA - 1)) {
            kDrop = (short)(1 + b_i);
            i3 = b_i + 3;
            if (i3 > 32767) {
              i3 = 32767;
            }

            lambdamin = Opt_data[i3 - 1];
          }
        }

        if (kDrop <= 0) {
          x_size[0] = 2;
          x_data[0] = Opt_data[0];
          x_data[1] = Opt_data[1];
          exitg3 = 2;
        } else {
          (*status)++;
          if (*status > 5.0) {
            ResetToColdStart(iA, iC);
            nA = 1;
            ColdReset = true;
          } else {
            lambda[iC[kDrop - 1] - 1] = 0.0;
            DropConstraint(kDrop, iA, &nA, iC);
          }
        }
      }
    } else {
      exitg3 = 2;
    }
  } while (exitg3 == 0);

  if (exitg3 == 1) {
  } else {
    if (nA <= 0) {
      lambda[0] = 0.0;
      lambda[1] = 0.0;
      lambda[2] = 0.0;
      Unconstrained(Hinv_data, Hinv_size, x_data);
    }

    Xnorm0 = b_norm(x_data);
    do {
      exitg2 = 0;
      if (*status <= 200.0) {
        cMin = -1.0E-6;
        kNext = 0;
        if (!cTolComputed) {
          a_data[0] = 0.0 * x_data[0];
          a_data[1] = x_data[1];
          b_abs(a_data, AcRow);
          if ((AcRow[0] < AcRow[1]) || (rtIsNaN(AcRow[0]) && (!rtIsNaN(AcRow[1]))))
          {
            lambdamin = AcRow[1];
          } else {
            lambdamin = AcRow[0];
          }

          if ((!(cTol[0] > lambdamin)) && (!rtIsNaN(lambdamin))) {
            cTol[0] = lambdamin;
          }
        }

        if (iA[0] == 0) {
          lambdamin = ((0.0 * x_data[0] + x_data[1]) - b[0]) / cTol[0];
          if (lambdamin < -1.0E-6) {
            cMin = lambdamin;
            kNext = 1;
          }
        }

        if (!cTolComputed) {
          a_data[0] = 0.0 * x_data[0];
          a_data[1] = -x_data[1];
          b_abs(a_data, AcRow);
          if ((AcRow[0] < AcRow[1]) || (rtIsNaN(AcRow[0]) && (!rtIsNaN(AcRow[1]))))
          {
            lambdamin = AcRow[1];
          } else {
            lambdamin = AcRow[0];
          }

          if ((!(cTol[1] > lambdamin)) && (!rtIsNaN(lambdamin))) {
            cTol[1] = lambdamin;
          }
        }

        if ((iA[1] == 0) && (((0.0 * x_data[0] + -x_data[1]) - b[1]) / cTol[1] <
                             cMin)) {
          kNext = 2;
        }

        cTolComputed = true;
        if (kNext <= 0) {
          exitg2 = 1;
        } else {
          do {
            exitg1 = 0;
            if ((kNext > 0) && (*status <= 200.0)) {
              AcRow[0] = 0.0;
              AcRow[1] = dv0[kNext + 2];
              guard1 = false;
              if (nA == 0) {
                if (Hinv_size[1] == 1) {
                  aoffset = Hinv_size[0];
                  for (i2 = 0; i2 < aoffset; i2++) {
                    z_data[i2] = 0.0;
                    for (i3 = 0; i3 < 1; i3++) {
                      z_data[i2] += Hinv_data[i2] * 0.0;
                    }
                  }
                } else {
                  m = Hinv_size[0];
                  inner = Hinv_size[1];
                  if (0 <= Hinv_size[0] - 1) {
                    memset(&z_data[0], 0, (unsigned int)(Hinv_size[0] * (int)
                            sizeof(double)));
                  }

                  for (k = 0; k < inner; k++) {
                    aoffset = k * m;
                    for (b_i = 0; b_i < m; b_i++) {
                      z_data[b_i] += AcRow[k] * Hinv_data[aoffset + b_i];
                    }
                  }
                }

                guard1 = true;
              } else {
                lambdamin = KWIKfactor(iC, nA, Linv_data, Linv_size, RLinv_data,
                  RLinv_size, D_data, D_size, H_data, H_size);
                if (lambdamin <= 0.0) {
                  *status = -2.0;
                  exitg1 = 1;
                } else {
                  aoffset = H_size[0] * H_size[1];
                  for (i2 = 0; i2 < aoffset; i2++) {
                    U_data[i2] = -H_data[i2];
                  }

                  if (H_size[1] == 1) {
                    aoffset = H_size[0];
                    for (i2 = 0; i2 < aoffset; i2++) {
                      z_data[i2] = 0.0;
                      for (i3 = 0; i3 < 1; i3++) {
                        z_data[i2] += U_data[i2] * 0.0;
                      }
                    }
                  } else {
                    m = H_size[0];
                    inner = H_size[1];
                    if (0 <= H_size[0] - 1) {
                      memset(&z_data[0], 0, (unsigned int)(H_size[0] * (int)
                              sizeof(double)));
                    }

                    for (k = 0; k < inner; k++) {
                      aoffset = k * m;
                      for (b_i = 0; b_i < m; b_i++) {
                        z_data[b_i] += AcRow[k] * U_data[aoffset + b_i];
                      }
                    }
                  }

                  i2 = nA;
                  for (b_i = 0; b_i < i2; b_i++) {
                    m = D_size[0] * b_i;
                    r_data[b_i] = 0.0 * D_data[m] + AcRow[1] * D_data[1 + m];
                  }

                  guard1 = true;
                }
              }

              if (guard1) {
                kDrop = 0;
                t1 = 0.0;
                isT1Inf = true;
                ColdReset = true;
                if (nA > 1) {
                  m = 0;
                  exitg4 = false;
                  while ((!exitg4) && (m <= nA - 2)) {
                    if (r_data[m] >= 1.0E-12) {
                      ColdReset = false;
                      exitg4 = true;
                    } else {
                      m++;
                    }
                  }
                }

                if ((nA == 1) || ColdReset) {
                } else {
                  i2 = nA - 1;
                  if (i2 < -32768) {
                    i2 = -32768;
                  }

                  for (b_i = 0; b_i < i2; b_i++) {
                    if (r_data[b_i] > 1.0E-12) {
                      lambdamin = lambda[iC[b_i] - 1] / r_data[b_i];
                      if ((kDrop == 0) || (lambdamin < rMin)) {
                        rMin = lambdamin;
                        kDrop = (short)(1 + b_i);
                      }
                    }
                  }

                  if (kDrop > 0) {
                    t1 = rMin;
                    isT1Inf = false;
                  }
                }

                lambdamin = z_data[0] * 0.0 + z_data[1] * dv0[kNext + 2];
                if (lambdamin <= 0.0) {
                  cMin = 0.0;
                  ColdReset = true;
                } else {
                  cMin = (b[kNext - 1] - (0.0 * x_data[0] + dv0[kNext + 2] *
                           x_data[1])) / lambdamin;
                  ColdReset = false;
                }

                if (isT1Inf && ColdReset) {
                  *status = -1.0;
                  exitg1 = 1;
                } else {
                  if ((t1 < cMin) || rtIsNaN(cMin)) {
                    lambdamin = t1;
                  } else {
                    lambdamin = cMin;
                  }

                  if (ColdReset) {
                    lambdamin = t1;
                  } else {
                    if (isT1Inf) {
                      lambdamin = cMin;
                    }
                  }

                  i2 = nA;
                  for (b_i = 0; b_i < i2; b_i++) {
                    m = iC[b_i] - 1;
                    lambda[m] -= lambdamin * r_data[b_i];
                    if ((iC[b_i] <= 2) && (lambda[m] < 0.0)) {
                      lambda[m] = 0.0;
                    }
                  }

                  lambda[kNext - 1] += lambdamin;
                  if (lambdamin == t1) {
                    DropConstraint(kDrop, iA, &nA, iC);
                  }

                  if (!ColdReset) {
                    x_size[0] = 2;
                    x_data[0] += lambdamin * z_data[0];
                    x_data[1] += lambdamin * z_data[1];
                    if (lambdamin == cMin) {
                      if (nA == 2) {
                        *status = -1.0;
                        exitg1 = 1;
                      } else {
                        i2 = nA + 1;
                        if (i2 > 32767) {
                          i2 = 32767;
                        }

                        nA = (short)i2;
                        iC[(short)i2 - 1] = kNext;
                        i = (short)i2;
                        exitg4 = false;
                        while ((!exitg4) && (i > 1)) {
                          i2 = i - 1;
                          kDrop = iC[i2];
                          i3 = i - 2;
                          if (iC[i2] > iC[i3]) {
                            exitg4 = true;
                          } else {
                            iC[i2] = iC[i3];
                            iC[i3] = kDrop;
                            i = (short)i2;
                          }
                        }

                        iA[kNext - 1] = 1;
                        kNext = 0;
                        (*status)++;
                      }
                    } else {
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                }
              }
            } else {
              lambdamin = b_norm(x_data);
              if (std::abs(lambdamin - Xnorm0) > 0.001) {
                Xnorm0 = lambdamin;
                c_abs(b, varargin_1);
                lambdamin = varargin_1[0];
                if (!(lambdamin > 1.0)) {
                  lambdamin = 1.0;
                }

                cTol[0] = lambdamin;
                lambdamin = varargin_1[1];
                if (!(lambdamin > 1.0)) {
                  lambdamin = 1.0;
                }

                cTol[1] = lambdamin;
                cTolComputed = false;
              }

              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = 1;
          }
        }
      } else {
        *status = 0.0;
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
}

//
// File trailer for qpkwik.cpp
//
// [EOF]
//
