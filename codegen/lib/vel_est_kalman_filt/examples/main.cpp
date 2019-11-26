//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:21:00
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include "vel_est_kalman_filt.h"
#include "main.h"
#include "vel_est_kalman_filt_terminate.h"
#include "vel_est_kalman_filt_initialize.h"

// Function Declarations
static void argInit_2x4_real_T(double result[8]);
static void argInit_4x4_real32_T(float result[16]);
static void argInit_4x4_real_T(double result[16]);
static float argInit_real32_T();
static double argInit_real_T();
static void main_vel_est_kalman_filt();

// Function Definitions

//
// Arguments    : double result[8]
// Return Type  : void
//
static void argInit_2x4_real_T(double result[8])
{
  int idx0;
  double result_tmp;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 2; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 2] = result_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 4] = argInit_real_T();

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 6] = argInit_real_T();
  }
}

//
// Arguments    : float result[16]
// Return Type  : void
//
static void argInit_4x4_real32_T(float result[16])
{
  int idx0;
  float result_tmp;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 4; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result_tmp = argInit_real32_T();
    result[idx0] = result_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 4] = result_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 8] = argInit_real32_T();

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 12] = argInit_real32_T();
  }
}

//
// Arguments    : double result[16]
// Return Type  : void
//
static void argInit_4x4_real_T(double result[16])
{
  int idx0;
  double result_tmp;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 4; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 4] = result_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 8] = argInit_real_T();

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 12] = argInit_real_T();
  }
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_vel_est_kalman_filt()
{
  double dv0[16];
  double dv1[8];
  float fv0[16];
  float fv1[16];
  float K[8];

  // Initialize function 'vel_est_kalman_filt' input arguments.
  // Initialize function input argument 'A'.
  // Initialize function input argument 'C'.
  // Initialize function input argument 'Q'.
  // Initialize function input argument 'Pm'.
  // Call the entry-point 'vel_est_kalman_filt'.
  argInit_4x4_real_T(dv0);
  argInit_2x4_real_T(dv1);
  argInit_4x4_real32_T(fv0);
  argInit_4x4_real32_T(fv1);
  vel_est_kalman_filt(dv0, dv1, fv0, argInit_real32_T(), fv1, K);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // Initialize the application.
  // You do not need to do this more than one time.
  vel_est_kalman_filt_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_vel_est_kalman_filt();

  // Terminate the application.
  // You do not need to do this more than one time.
  vel_est_kalman_filt_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
