function accel_new = ACC_P_test(rel_velx, rel_vely, rel_posx, rel_posy, vel_egox, vel_egoy) %#codegen
% Proportional Control
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

minDist = 0.4;         % Distance between the vehicles in meters.
%Kp = 0.26;
Kp = 0.5;
%Ki = 0.001;
%Kd = 1.0;
deltaT = 0.01;
err = intmax;

    err = rel_posx - minDist;
    Out = (Kp * err); % only P controller
    if Out >= 0
        accel_new = Out;
    else
        accel_new = single(0.0);


% Display in command window
%disp(['##1 -- PI Error :',num2str(err)])
%disp(['##2 -- Acceleration Command : ',num2str(accel_new)])
%disp(['##3 -- Integral : ',num2str(inte)])
%disp(['##4 -- Distance : ',num2str(rel_posx)])
%disp(['##4 -- Out : ',num2str(Out)])
end
