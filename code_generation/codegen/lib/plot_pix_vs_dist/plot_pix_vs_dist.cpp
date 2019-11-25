//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: plot_pix_vs_dist.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-Oct-2019 20:46:56
//

// Include Files
#include <cmath>
#include <math.h>
#include "rt_nonfinite.h"
#include "plot_pix_vs_dist.h"

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = std::abs(u0);
    d1 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = 1.0;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

//
// dist_x = [0.3; 0.4; 0.5; 0.6; 0.7; 0.8; 0.9; 1; 1.1; 1.2; 1.3; 1.4; 1.5; 1.6; 1.7; 1.8; 1.9; 2; 2.1; 2.2];
// Arguments    : double pixel_width
// Return Type  : double
//
double plot_pix_vs_dist(double pixel_width)
{
  double x_rel_dist;

  // width_pixels = [280; 181; 169; 140; 127; 100; 92; 84; 77; 72; 70; 64; 59; 54; 49; 48; 46; 45; 44; 42]; 
  // plot (width_pixels, dist_x )
  // ylabel('RELATIVE DISTANCE OF TURTLEBOT')
  // xlabel('width of turtlebot in pixels')
  //  According to the plot we can get the interpolating polynomial which can satisfy the value 
  //  of the y= relative distance and x= width in pixels
  //  Taking exponential function to fit the curve:
  // x = [.18; .25; .335; .41; .50; .60; .70; .83; .90; 1.00; 1.10; 1.20; 1.30]; 
  // x_rel_dist = 0.3809258 + 4.681089*e^(-0.02398154*pixel_width) use this or bottom one!! 
  // x_rel_dist = 0.04417456 + (1983352 - 0.04417456)/(1 +
  // (pixel_width/0.0001949206)^1.120355); older equation
  // x_rel_dist = -0.009777765 + (16.48311 + 0.009777765)/(1 +
  // (pixel_width/6.138883)^1.024073); new one
  //  -- Moving Average Filter
  // {
  // window = 20;
  // b = (1/window)*ones(1,window);
  // a = 1;
  // filt_pxl_width = filter(b,a,pixel_width);
  // }
  // x_rel_dist = 74.788*pixel_width^(-0.966); % 640X480 Image
  x_rel_dist = 56.815 * rt_powd_snf(pixel_width, -1.006);

  //  410X308 Image
  // end
  // hold on
  // plot(x, y)
  // xlabel('relative distance')
  // ylabel('width in pixels')
  return x_rel_dist;
}

//
// File trailer for plot_pix_vs_dist.cpp
//
// [EOF]
//
