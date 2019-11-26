//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: lds_convert.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-Oct-2019 21:08:10
//

// Include Files
#include <cmath>
#include "lds_convert.h"
#include "lds_convert_emxutil.h"

// Function Definitions

//
// This function converts the Lidar detections into [x, y] coordinates.
//  at different degrees of the detections.
// Arguments    : const emxArray_real_T *detect_rad
//                emxArray_real_T *x_y_coord
// Return Type  : void
//
void lds_convert(const emxArray_real_T *detect_rad, emxArray_real_T *x_y_coord)
{
  int i0;
  int k;
  emxArray_int32_T *r0;
  double x[30];
  static const double b_x[30] = { 0.26179938779914941, 0.24434609527920614,
    0.22689280275926285, 0.20943951023931956, 0.19198621771937624,
    0.17453292519943295, 0.15707963267948966, 0.13962634015954636,
    0.12217304763960307, 0.10471975511965978, 0.087266462599716474,
    0.069813170079773182, 0.05235987755982989, 0.034906585039886591,
    0.017453292519943295, -0.0, -0.017453292519943295, -0.034906585039886591,
    -0.05235987755982989, -0.069813170079773182, -0.087266462599716474,
    -0.10471975511965978, -0.12217304763960307, -0.13962634015954636,
    -0.15707963267948966, -0.17453292519943295, -0.19198621771937624,
    -0.20943951023931956, -0.22689280275926285, -0.24434609527920614 };

  double c_x[30];
  double d_x;

  //  flipping the array values to make values in the form (60: 1 : 360 : 301) degree values. 
  //  i.e. [60: 0: -59] degrees.
  // theta = [flip(linspace(1, length(detect_rad(1:60)), length(detect_rad(1:60)))), -linspace(0, length(detect_rad(61:120))-1, length(detect_rad(61:120)))]; 
  i0 = x_y_coord->size[0] * x_y_coord->size[1];
  x_y_coord->size[0] = detect_rad->size[0];
  x_y_coord->size[1] = 2;
  emxEnsureCapacity_real_T(x_y_coord, i0);
  k = detect_rad->size[0] << 1;
  for (i0 = 0; i0 < k; i0++) {
    x_y_coord->data[i0] = 0.0;
  }

  for (k = 0; k < 30; k++) {
    x[k] = std::cos(b_x[k]);
    c_x[k] = std::sin(b_x[k]);
  }

  emxInit_int32_T(&r0, 1);
  k = detect_rad->size[0];
  i0 = r0->size[0];
  r0->size[0] = k;
  emxEnsureCapacity_int32_T(r0, i0);
  for (i0 = 0; i0 < k; i0++) {
    r0->data[i0] = i0;
  }

  for (i0 = 0; i0 < 30; i0++) {
    d_x = detect_rad->data[i0] * x[i0];
    x[i0] = d_x;
  }

  k = r0->size[0];
  for (i0 = 0; i0 < k; i0++) {
    x_y_coord->data[r0->data[i0]] = x[i0];
  }

  k = x_y_coord->size[0];
  i0 = r0->size[0];
  r0->size[0] = k;
  emxEnsureCapacity_int32_T(r0, i0);
  for (i0 = 0; i0 < k; i0++) {
    r0->data[i0] = i0;
  }

  for (i0 = 0; i0 < 30; i0++) {
    d_x = detect_rad->data[i0] * c_x[i0];
    c_x[i0] = d_x;
  }

  k = r0->size[0];
  for (i0 = 0; i0 < k; i0++) {
    x_y_coord->data[r0->data[i0] + x_y_coord->size[0]] = c_x[i0];
  }

  emxFree_int32_T(&r0);

  // x_y_coord(:, 3) = 0.18; %the height of the Lidar placed on the turtlebot.
}

//
// File trailer for lds_convert.cpp
//
// [EOF]
//
