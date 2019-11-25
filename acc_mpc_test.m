function accel_new = acc_mpc_test(rel_velx, rel_vely, rel_posx, rel_posy, vel_egox, vel_egoy)
%  MPC, solving QP problem: min (0.5*x'*H*x + f' * x) with
% linear inequality constraint A*x >= b
% speed: current speed
% accele_new: spit out the velocity of the turtlebot
% brake: stop while no movement of the lead vehicle vel_ego = accele_new =0.
% rel_dist : rel_posx distance between the ego and lead vehicle.
% vel_egox:  current speed of ego robot. this info will be
% taken from the imu of the vehicle/turtlebot.
% x_des: safe distance to be considered on the actual vehicle for braking
% is 0.4m in this case

% using reletive distance minimization.
% Cost function: minimize J = |x_rel - x_des|^2
% Main constraint is Dis_rel - D_safe >= 0. which is derived through
% ego velocity constraint i.e. 0< vel_egox < 0.2 m/s

x_des = 0.40; % minimum distance is 40 cm.
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

     if rel_posx < x 
         accel_new = 0.0;
     else
         accel_new = (rel_velx + vel_egox);% + ((rel_posx - x) * 0.4);
     end
 else
       accel_new = vel_egox;   
 end

% disp(['##1 -- Status : ',num2str(stat)])
% disp(['##2 -- relative position : ',num2str(rel_posx)])
% disp(['##2 -- ego velocity : ',num2str(vel_egox)])
% disp(['##2 -- relative velocity : ',num2str(rel_velx)])
% disp(['##2 -- Acceleration Command : ',num2str(accel_new)])
end