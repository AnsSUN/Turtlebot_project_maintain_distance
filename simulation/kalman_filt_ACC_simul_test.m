clc, clear all, close all

dt = 0.4;
A = [1, 0, dt, 0;
                0, 1, 0, dt;
                0, 0, 1, 0;
                 0, 0, 0, 1];
             
C = [1, 0, 0, 0;
     0, 1, 0, 0];

R = [0.0025];
Q = [0.035, 0, 0, 0;
      0, 0.035, 0, 0;
      0, 0, 0.035, 0;
      0, 0, 0, 0.035];
P0 = [0.035, 0, 0, 0;
       0, 0.035, 0, 0;
        0, 0, 0.035, 0
        0, 0, 0, 0.035];
   
%% creating data to simulate:
%
state = ([sqrt(P0(1,1))*normrnd(0,1);
         sqrt(P0(2,2))*normrnd(0,1);
         sqrt(P0(3,3))*normrnd(0, 1);
         sqrt(P0(4,4))*normrnd(0, 1)]);

 
% state = 2*([0.1;
%          0.01;
%          0;
%          0]);
     
pose_true = [];
veltrue = [];
measurement = [];
for i = 1:1000
    pose_true = [pose_true, state(1:2)];
    veltrue = [veltrue, state(3:4)];
    measurement = [measurement, C*state + sqrt(R(1,1))*randn(1)];
    process_noise = [sqrt(Q(1,1))*randn(1);
                    sqrt(Q(2,2))*randn(1);
                    sqrt(Q(3,3))*randn(1);
                    sqrt(Q(4,4))*randn(1)];
    state = (A*(abs(state)) + process_noise);   
end

initialState = [0;0;0;0];
KF = trackingKF('MotionModel','2D Constant Velocity','State',initialState);
vx = 0.2;
vy = 0.1;
T  = 0.4;
pos = [0:vx*T:2;5:vy*T:6]';


 % run KF to the data:
 sem = [0, 0, 0, 0]';
 pose = [];
 vele_x = [];
 acc_vel = veltrue(1,1);
 y_vel = 0.01;
 acc_vel_save =[];
 %measurement = C*state + sqrt(R(1,1))*randn(1);
% measurement step
for i = 1:length(pose_true)
    Pm = P0;
    [K] = vel_est_kalman_filt(A, C, Q, R, Pm);
    sep = sem + K*(measurement(:,i) - C*sem);
    pose = [pose, sep(1:2)];
    vele_x = [vele_x, sep(3:4)];
 % prediction step
    sem = A*sep; %+ B*vele; % pass this final value
    acc_vel = acc_mpc_test(vele_x(1,i), vele_x(2,i), measurement(1,i), measurement(2,i), acc_vel, y_vel);
    acc_vel_save = [acc_vel_save, acc_vel];
end

% compare and plot kalman filter output
j = 1:length(pose);
figure()
ax(1) = subplot(3,1,1);
%figure(1)
plot(j, pose(1,:), 'b', j, pose_true(1,:), 'r')
legend('KF position x(after measured)', 'true position x')
xlabel('sample 100')
ylabel('relative position of the lead bot')
title('Comparing actual distance between Kalman estimated distance(observed)')
grid on
hold on
% figure(2)
% plot(j, pose(2,:), 'b', j, pose_true(2,:), 'r')
% legend('KF position y', 'true position y')
% xlabel('sample 100')

%figure(2)
ax(2) = subplot(2,1,2);
plot(j, vele_x(1,:), 'b', j, veltrue(1,:), 'r')
legend('KF velocity x', 'true velocity x')
xlabel('sample 100')
ylabel('relative velocity of the bot')
title('Velocity estimated by Kalman filter through distance measurement')
% hold off
grid on

% figure(4)
% plot(j, vele_x(2,:), 'b', j, veltrue(2,:), 'r')
% legend('KF velocity y', 'true velocity y')
% xlabel('sample 100')

%figure(3)
ax(3) = subplot(4,1,2);
plot(j, acc_vel_save, 'b')
legend('ACC velocity x', 'true velocity x')
xlabel('sample 100')
ylabel('velocity of the lead bot')
title('Velocity estimated by ACC')
grid on
linkaxes(ax,'x')
%

%{
%%  simulate sensor ACC through sensor measurement:

%ego_bot_vel_pt07_load = load('V_x_relsave_plot_const_vel_pt07.mat');
%ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot_const_vel_pt07.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save;

 sem = [0, 0, 0, 0]';
 pose = [];
 vele_x = [];
 acc_vel = veltrue(1,1);
 y_vel = 0.01;
 acc_vel_save =[];
 %measurement = C*state + sqrt(R(1,1))*randn(1);
% measurement step
for i = 1:length(ego_bot_dist_pt07)
    Pm = P0;
    [K] = vel_est_kalman_filt(A, C, Q, R, Pm);
    sep = sem + K*(measurement(:,i) - C*sem);
    pose = [pose, sep(1:2)];
    vele_x = [vele_x, sep(3:4)];
 % prediction step
    sem = A*sep; %+ B*vele; % pass this final value
    acc_vel = acc_mpc_test(vele_x(1,i), vele_x(2,i), measurement(1,i), measurement(2,i), acc_vel, y_vel);
    acc_vel_save = [acc_vel_save, acc_vel];
end

indx_pt07 = 1:length(ego_bot_dist_pt07);
%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_dist_pt07),1);
const_vel_plot = 0.07*ones(length(ego_bot_dist_pt07),1);

figure(1)

% ax(1) = subplot(2,1,1);
% plot(indx_pt07, error_dist_pt07, 'r', indx_pt07, zero_dist_plot, 'b')
% xlabel('Time')
% ylabel('Error (in m)')
% title('Error to maintain the distance between lead and ego vehicle (m)')
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:169), ego_bot_dist_pt07(1:169), 'r', indx_pt07(1:169), const_dist_plot(1:169), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m)')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:169), ego_bot_vel_pt07(1:169), 'r', indx_pt07(1:169), const_vel_plot(1:169), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead ego vehicle by ACC (m/s)')
hold off

%}

