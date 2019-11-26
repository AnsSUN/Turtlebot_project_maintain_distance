//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
// File: new_mpc_test.cpp
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
#include "inv.h"

// Function Definitions

//
// ACC ago with MPC, solving QP problem: min (0.5*x'*H*x + f' * x) with
//  linear inequality constraint A*x >= b
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
double new_mpc_test(float rel_velx, float, float rel_posx, float, double
                    vel_egox, double)
{
  double accel_new;
  double Linv_data[4];
  int inner;
  int j;
  boolean_T exitg1;
  double L_data[4];
  int jj;
  double ajj;
  int boffset;
  int L_size[2];
  int n;
  int k;
  int Linv_size[2];
  int Hinv_size[2];
  double dv1[3];
  int coffset;
  int Hinv_data_tmp;
  double Hinv_data[4];
  double x_data[2];
  int x_size[1];
  double lam[3];
  short iA1[3];
  int aoffset;
  int i;

  //  using reletive velocity minimization.
  //  Cost function to minimize J = |V - V_set|^2.
  //  Main constraint is Dis_rel - D_safe >= 0. which is derived through
  //  integral of velocity i .e. V * t >= D_safe.
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%velocity model cost
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%function
  // {
  // persistent time_rel
  // currTime = datetime;
  //
  // if isempty(time_rel)
  //     time_rel = currTime;
  // end
  // dt= seconds(currTime - time_rel);
  // dt = 2;
  //
  // D_safe = 0.30; % safe distance is 30 cm.
  //
  // H = [2 -2; -2 2];
  // f = [0; 0];
  //
  //  setting v_ego >=0 and v_set >=0, V * t >= D_safe, v_ego < 0.2, v_set < 0.2. 
  // A = [ 0 dt; 1 0; 0 1];
  // b = [D_safe; 0; 0];
  //
  // iA0 = true;
  // iA0nxt = false(size(b)-[1, 0]);
  // iA0 = [iA0; false(size(b)-[1, 0])]; % iA0 = false(size(b));
  // Aeq = [0, 1]; % check with someone
  // beq = [double(rel_velx)]; % check with someone % change it to lead vehicle velocity 
  //
  //
  // if dt==0
  //     accel_new = 0; % because of comparing afterwards.
  // else
  //     for iter = 1:10
  //         [L,p] = chol(H,'lower');
  //         Linv = inv(L);
  //
  //         opt = mpcqpsolverOptions;
  //
  // cold start the solver, inequality constraints
  //         [x,stat, iA] = mpcqpsolver(Linv,f,A,b,Aeq,beq,iA0,opt);
  //         iA0 = iA;
  //    end
  //
  //    if (stat > 0)
  //         accel_new = x(2,:);
  //     else
  //         accel_new = 0;
  //    end
  // end
  // }
  //  persistent ini_ego_vel
  //  if isempty(ini_ego_vel)
  //      ini_ego_vel =0.01;
  //      vel_egox = ini_ego_vel;
  //  end
  // %% relative Distance cost function %%%%%%
  //  minimize J = |V - v_ego|^2
  //  const_vel = 0.02; % to keep the velocity of the turtlebot.
  //  minimum distance is 40 cm.
  Linv_data[0] = 2.0;
  Linv_data[1] = 0.0;
  Linv_data[2] = 0.0;
  Linv_data[3] = 0.0001;
  inner = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 2)) {
    jj = j + (j << 1);
    ajj = 0.0;
    if (j >= 1) {
      ajj = Linv_data[1] * Linv_data[1];
    }

    ajj = Linv_data[jj] - ajj;
    if (ajj > 0.0) {
      ajj = std::sqrt(ajj);
      Linv_data[jj] = ajj;
      if (j + 1 < 2) {
        jj += 2;
        ajj = 1.0 / ajj;
        L_data[0] = Linv_data[0];
        L_data[1] = Linv_data[1];
        L_data[2] = Linv_data[2];
        L_data[3] = Linv_data[3];
        for (k = jj; k <= jj; k++) {
          L_data[k - 1] *= ajj;
        }

        memcpy(&Linv_data[0], &L_data[0], (unsigned int)(4 * (int)sizeof(double)));
      }

      j++;
    } else {
      Linv_data[jj] = ajj;
      inner = j + 1;
      exitg1 = true;
    }
  }

  L_data[0] = Linv_data[0];
  L_data[1] = Linv_data[1];
  L_data[2] = Linv_data[2];
  L_data[3] = Linv_data[3];
  if (inner == 0) {
    jj = 2;
  } else {
    jj = inner - 1;
  }

  if (2 <= jj) {
    L_data[2] = 0.0;
  }

  if (1 > jj) {
    boffset = 0;
    jj = 0;
  } else {
    boffset = jj;
  }

  for (inner = 0; inner < jj; inner++) {
    for (n = 0; n < boffset; n++) {
      Linv_data[n + boffset * inner] = L_data[n + (inner << 1)];
    }
  }

  L_size[0] = boffset;
  L_size[1] = jj;
  boffset *= jj;
  if (0 <= boffset - 1) {
    memcpy(&L_data[0], &Linv_data[0], (unsigned int)(boffset * (int)sizeof
            (double)));
  }

  inv(L_data, L_size, Linv_data, Linv_size);

  // Linv = reshape(Linv,1,1);
  //  PI constants
  //  checked and calculated through documentation: http://emanual.robotis.com/docs/en/dxl/x/xl430-w250/#velocity-i-gain 
  //  checked and calculated through documentation: http://emanual.robotis.com/docs/en/dxl/x/xl430-w250/#velocity-i-gain 
  // cold start the solver, inequality constraints
  boffset = Linv_size[0];
  for (inner = 0; inner < boffset; inner++) {
    jj = Linv_size[1];
    for (n = 0; n < jj; n++) {
      L_data[n + Linv_size[1] * inner] = Linv_data[inner + Linv_size[0] * n];
    }
  }

  if (Linv_size[0] == 1) {
    Hinv_size[0] = Linv_size[1];
    Hinv_size[1] = Linv_size[1];
    boffset = Linv_size[1];
    for (inner = 0; inner < boffset; inner++) {
      jj = Linv_size[1];
      for (n = 0; n < jj; n++) {
        Hinv_data_tmp = inner + Hinv_size[0] * n;
        Hinv_data[Hinv_data_tmp] = 0.0;
        for (coffset = 0; coffset < 1; coffset++) {
          Hinv_data[Hinv_data_tmp] += L_data[inner] * Linv_data[n];
        }
      }
    }
  } else {
    jj = Linv_size[1];
    inner = Linv_size[0];
    n = Linv_size[1];
    Hinv_size[0] = Linv_size[1];
    Hinv_size[1] = Linv_size[1];
    for (j = 0; j < n; j++) {
      coffset = j * jj;
      boffset = j * inner;
      if (0 <= jj - 1) {
        memset(&Hinv_data[coffset], 0, (unsigned int)(((jj + coffset) - coffset)
                * (int)sizeof(double)));
      }

      for (k = 0; k < inner; k++) {
        aoffset = k * jj;
        ajj = Linv_data[boffset + k];
        for (i = 0; i < jj; i++) {
          Hinv_data_tmp = coffset + i;
          Hinv_data[Hinv_data_tmp] += ajj * L_data[aoffset + i];
        }
      }
    }
  }

  dv1[0] = -0.0;
  dv1[1] = -0.2;
  dv1[2] = rel_posx + (rel_velx + (float)vel_egox) * 0.4F;
  qpkwik(Linv_data, Linv_size, Hinv_data, Hinv_size, dv1, x_data, x_size, lam,
         &ajj, iA1);

  //  persistent err_old
  //  if isempty(err_old)
  //      err_old = 0;
  //  end
  // if rel_velx > -0.2 & rel_velx < 0.2
  if (ajj > 0.0) {
    // if x ~= x_des
    // accel_new = rel_velx + vel_egox + const_vel;
    //
    accel_new = x_data[1];

    //              err = rel_posx - x;     % Positive error means vehicle is far. 
    //              % err_old = err;
    //              int_err = err_old + ((err - err_old) * 0.4);
    //              accel_new = (Kp * err) + (Ki * int_err);
    //              err_old = err;
  } else {
    accel_new = vel_egox;
  }

  // else
  // accel_new = vel_egox;
  //
  //     %{
  //     if rel_posx <= x & rel_posx >= 0.3
  //          accel_new = vel_egox; %0.0;
  //     elseif rel_posx <=0.25
  //         accel_new = 0.0;
  //     end
  //      %}
  //   else
  //       accel_new = 0.0;
  // end
  //  disp(['##1 -- Status : ',num2str(stat)])
  //  disp(['##2 -- relative position : ',num2str(rel_posx)])
  //  disp(['##2 -- ego velocity : ',num2str(vel_egox)])
  //  disp(['##2 -- relative velocity : ',num2str(rel_velx)])
  //  disp(['##2 -- Acceleration Command : ',num2str(accel_new)])
  return accel_new;
}

//
// File trailer for new_mpc_test.cpp
//
// [EOF]
//
