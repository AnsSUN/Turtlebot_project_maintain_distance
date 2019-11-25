function accel_new = ACC_PI_test(rel_velx, rel_vely, rel_posx, rel_posy, vel_egox, vel_egoy) %#codegen
%  Proportional Integral PI Controller 
% accele_new: spit out the velocity of the turtlebot
% brake: stop while no movement of the lead vehicle vel_ego = accele_new =0.
% rel_dist : rel_posx distance between the ego and lead vehicle.
% vel_egox:  current speed of ego robot. this info will be
% taken from the imu of the vehicle/turtlebot.
% x_des: safe distance to be considered on the actual vehicle for braking
% is 0.4m in this case

% Main constraint is Dis_rel - D_safe >= 0. which is derived through
% ego velocity constraint i.e. 0< vel_egox < 0.2 m/s
% kp, ki for PI
% dist_safe: safe distance to be considered on the actual vehicle for braking but for
% this turtlebot application it is 0


persistent err_old
if isempty(err_old)
    err_old = 0;
end

minDist = 0.4;         % Distance between the vehicles in meters.
%Kp = 0.26;
%Ki = 0.001;
Kp = 0.5;
Ki = 0.01;

deltaT = 0.01;
err = intmax;

    err = rel_posx - minDist;
 
    int_err = err_old + ((err - err_old) * 0.4); % dt = 0.4
    Out = (Kp * err) + (Ki * int_err); % PI controller
    % anti-windup error
    if Out > 1
        accel_new = 0.2;
        Out1 = 1;
        Ki = 0;
    elseif Out < -0.05
        accel_new =0.0;
        Out1 = 0;
        Ki = 0;
        
    else
        accel_new = double(Out);

        Out1 = double(Out);
        %Ki = 0.001;
        Ki = 0.01;
    end
    err_old = double(err);
    Out = Out1;

% Display in command window
%disp(['##1 -- PI Error :',num2str(err)])
%disp(['##2 -- Acceleration Command : ',num2str(accel_new)])
%disp(['##3 -- Integral : ',num2str(inte)])
%disp(['##4 -- Distance : ',num2str(rel_posx)])
%disp(['##4 -- Out : ',num2str(Out)])
end