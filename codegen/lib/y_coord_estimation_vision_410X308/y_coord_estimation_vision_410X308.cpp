//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: y_coord_estimation_vision_410X308.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 14-Oct-2019 20:50:36
//

// Include Files
#include "y_coord_estimation_vision_410X308.h"

// Function Definitions

//
// bboxes2 = [475, 330, 130, 110]; % this is the reference bounding box for calculation. for 640X480 image
// Arguments    : double pix_fromx
//                double x_rel_dist_vis
// Return Type  : double
//
double y_coord_estimation_vision_410X308(double pix_fromx, double x_rel_dist_vis)
{
  //  calculating the y coordinate from the image
  //  line([320, 320], [0, 480]) %vertical line on image for reference.
  //   bboxes1 = [65, 320, 130, 110];
  //   bboxes2 = [475, 330, 130, 110];
  //  pix_fromx : x pixel centroid point from image (0,0) i.e. x + (width/2)
  // for 410X308 image
  //  change 320 i.e. 1/2*(size of image in x direction) value according to pixel size of the image 
  //  constant
  //  change 320 i.e. 1/2*(size of image in x direction) value according to pixel size of the image 
  // pixel value change according to position.
  return (pix_fromx - 205.0) * x_rel_dist_vis / 410.0;
}

//
// File trailer for y_coord_estimation_vision_410X308.cpp
//
// [EOF]
//
