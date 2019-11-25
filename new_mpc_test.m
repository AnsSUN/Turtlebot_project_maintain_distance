function [accel_new] = new_mpc_test(rel_velx, rel_vely, rel_posx, rel_posy, vel_egox, vel_egoy) %#codegen
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

delta_t = 0.4;
x_des = 0.4; % minimum distance is 40 cm.
v_lead = rel_velx + vel_egox;
H = [2, 0; 
    0, 0.0001];
f= [-2*x_des; 0];
A = [0, 1;
    0, -1];
b = [0; -0.2];
iA0 = false(size(b));
Aeq = [1, delta_t];
beq = double(rel_posx + v_lead*delta_t);

[L,p] = chol(H,'lower');
Linv = inv(L);
%Linv = reshape(Linv,1,1);

opt = mpcqpsolverOptions;

%cold start the solver, inequality constraints
[x,stat,iA] = mpcqpsolver(Linv,f,A,b,Aeq,beq,iA0,opt);
if rel_velx < 0
    accel_new =0;
end

    if stat > 0
        accel_new =  x(2);
        
    else
           accel_new = vel_egox;
    end

% disp(['##1 -- Status : ',num2str(stat)])
% disp(['##2 -- relative position : ',num2str(rel_posx)])
% disp(['##2 -- ego velocity : ',num2str(vel_egox)])
% disp(['##2 -- relative velocity : ',num2str(rel_velx)])
% disp(['##2 -- Acceleration Command : ',num2str(accel_new)])
end

