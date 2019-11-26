//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: ACC_PI_test.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 15-Oct-2019 17:29:12
//

// Include Files
#include "ACC_PI_test.h"

// Variable Definitions
static double err_old;

// Function Definitions

//
// ACC ago with PID
//  speed: current speed
//  accele_new: spit out acceleration to change the velocity of the turtlebot
//  brake: stop while no movement of the lead vehicle vel_ego=0.
//  rel_dist : rel_posx distance between the ego and lead vehicle.
//  v_ego: cruise speed to maintain the minimum distance.
//  max_dist: maximum relative distance to have ACC mode on, this is doing
//  because to the sensors has some ranges such as lidar has 3.5 meter range
//  and vision can also detect object till some distance. Therefore, in this
//  case, the maximum distance should be 2.5 m to 3.0 m.
//  vel_ego: to change the acceleration of the vehicle. this info will be
//  taken from the imu of the vehicle/turtlebot.
//  kp, ki, kd for PID
//  dist_safe: safe distance to be considered on the actual vehicle for braking but for
//  this turtlebot application it is 0
// Arguments    : float rel_velx
//                float rel_vely
//                float rel_posx
//                float rel_posy
//                double vel_egox
//                double vel_egoy
// Return Type  : double
//
double ACC_PI_test(float, float, float rel_posx, float, double, double)
{
  double accel_new;
  float Out;

  // rel_distx = rel_posx;
  // rel_disty = rel_posy;
  // dist_safe = 0;
  // max_dist = 2.5; % in meters.
  // if (rel_distx < 0)
  //     accel_new = 0;
  // end
  // if ((rel_distx - dist_safe)>= 0 && (rel_distx - dist_safe)<= max_dist)
  //     accel_new = rel_velx + vel_ego;
  //    end
  //  Check the application of PID to maintain the distance of the vehicle and
  //  apply it in this algorithm.
  //  persistent inte Ki
  //  if isempty(inte)
  //      inte = 0;
  //  end
  //  if isempty(Ki)
  //      Ki = 0.001;
  //  end
  //  Distance between the vehicles in meters.
  // Kp = 0.26;
  // Ki = 0.001;
  // Kd = 1.0;
  //  Out1 = 0; % check with Aman
  //  ----
  // while (err > 0.01) % change any after clustering algorithm
  // inte = inte + (Ki * err);
  //  dt = 0.4
  Out = 0.5F * (rel_posx - 0.4F) + 0.01F * ((float)err_old + ((rel_posx - 0.4F)
    - (float)err_old) * 0.4F);

  //  PI controller
  // Out = (Kp * err); % only P controller
  if (Out > 1.0F) {
    accel_new = 0.2;
  } else if (Out < -0.05) {
    accel_new = 0.0;
  } else {
    accel_new = Out;

    // Ki = 0.001;
  }

  err_old = rel_posx - 0.4F;

  //  Display in command window
  // disp(['##1 -- PI Error :',num2str(err)])
  // disp(['##2 -- Acceleration Command : ',num2str(accel_new)])
  // disp(['##3 -- Integral : ',num2str(inte)])
  // disp(['##4 -- Distance : ',num2str(rel_posx)])
  // disp(['##4 -- Out : ',num2str(Out)])
  return accel_new;
}

//
// Arguments    : void
// Return Type  : void
//
void ACC_PI_test_init()
{
  err_old = 0.0;
}

//
// File trailer for ACC_PI_test.cpp
//
// [EOF]
//
