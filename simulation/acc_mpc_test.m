function accel_new = acc_mpc_test(rel_velx, rel_vely, rel_posx, rel_posy, vel_egox, vel_egoy)
% ACC ago with MPC, solving QP problem: min (0.5*x'*H*x + f' * x) with
% linear inequality constraint A*x >= b
% speed: current speed
% accele_new: spit out acceleration to change the velocity of the turtlebot
% brake: stop while no movement of the lead vehicle vel_ego=0.
% rel_dist : rel_posx distance between the ego and lead vehicle.
% v_ego: cruise speed to maintain the minimum distance.
% max_dist: maximum relative distance to have ACC mode on, this is doing
% because to the sensors has some ranges such as lidar has 3.5 meter range
% and vision can also detect object till some distance. Therefore, in this
% case, the maximum distance should be 2.5 m to 3.0 m.
% vel_ego: to change the acceleration of the vehicle. this info will be
% taken from the imu of the vehicle/turtlebot.
% dist_safe: safe distance to be considered on the actual vehicle for braking but for
% this turtlebot application it is 0

% using reletive velocity minimization.
% Cost function to minimize J = |V - V_set|^2.
% Main constraint is Dis_rel - D_safe >= 0. which is derived through
% integral of velocity i .e. V * t >= D_safe.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%velocity model cost
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%function
%{
persistent time_rel
currTime = datetime;

if isempty(time_rel)
    time_rel = currTime;
end
dt= seconds(currTime - time_rel);
%dt = 2;

D_safe = 0.30; % safe distance is 30 cm.
   
H = [2 -2; -2 2];
f = [0; 0];

% setting v_ego >=0 and v_set >=0, V * t >= D_safe, v_ego < 0.2, v_set < 0.2.
A = [ 0 dt; 1 0; 0 1];
b = [D_safe; 0; 0];

iA0 = true;
%iA0nxt = false(size(b)-[1, 0]);
iA0 = [iA0; false(size(b)-[1, 0])]; % iA0 = false(size(b));
Aeq = [0, 1]; % check with someone
beq = [double(rel_velx)]; % check with someone % change it to lead vehicle velocity

    
if dt==0
    accel_new = 0; % because of comparing afterwards.
else
    for iter = 1:10
        [L,p] = chol(H,'lower');
        Linv = inv(L);

        opt = mpcqpsolverOptions;

%cold start the solver, inequality constraints
        [x,stat, iA] = mpcqpsolver(Linv,f,A,b,Aeq,beq,iA0,opt);
        iA0 = iA;
   end

   if (stat > 0)
        accel_new = x(2,:);
    else
        accel_new = 0;
   end
end
%}

%%% relative Distance cost function %%%%%%
% minimize J = |x_rel - x_des|^2
const_vel = 0.02; % to keep the velocity of the turtlebot.
x_des = 0.40; % minimum distance is 30 cm.
H = 2;
f= -2*x_des;
A = [1];
b = [x_des];
iA0 = false(size(b));
Aeq = [];
beq = zeros(0,1);

[L,p] = chol(H,'lower');
Linv = inv(L);

opt = mpcqpsolverOptions;

%cold start the solver, inequality constraints
[x,stat, iA] = mpcqpsolver(Linv,f,A,b,Aeq,beq,iA0,opt);
if rel_velx < 0
    rel_velx =0;
end

 if stat > 0
     %if x ~= x_des
         accel_new = rel_velx + vel_egox; %+ const_vel;
    % else
       %  accel_new = vel_egox;
     %end
     %
     if rel_posx <= x 
         accel_new = 0.0;
     end
     %
    %{
    if rel_posx <= x & rel_posx >= 0.3
         accel_new = vel_egox; %0.0;
    elseif rel_posx <=0.25
        accel_new = 0.0;
    end
     %}
%  else
%      accel_new = 0.0;   
 end

% disp(['##1 -- Status : ',num2str(stat)])
% disp(['##2 -- relative position : ',num2str(rel_posx)])
% disp(['##2 -- ego velocity : ',num2str(vel_egox)])
% disp(['##2 -- relative velocity : ',num2str(rel_velx)])
% disp(['##2 -- Acceleration Command : ',num2str(accel_new)])
end
