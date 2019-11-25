clc, clear all, close all

dt = 0.4;
A = [1, 0, dt, 0;
                0, 1, 0, dt;
                0, 0, 1, 0;
                 0, 0, 0, 1];
             
C = [1, 0, 0, 0;
     0, 1, 0, 0];

R = [0.000225];
Q = [0.0001, 0, 0, 0;
      0, 0.0001, 0, 0;
      0, 0, 0.0001, 0;
      0, 0, 0, 0.0001];
P0 = [0.0001, 0, 0, 0;
       0, 0.0001, 0, 0;
        0, 0, 0.0001, 0
        0, 0, 0, 0.0001];
   
% creating data to simulate:

state = [sqrt(P0(1,1))*normrnd(0,1);
         sqrt(P0(2,2))*normrnd(0,1);
         sqrt(P0(3,3))*normrnd(0, 1);
         sqrt(P0(4,4))*normrnd(0, 1)];

pose_true = [];
veltrue = [];
measurement = [];
for i = 1:100
    pose_true = [pose_true, state(1:2)];
    veltrue = [veltrue, state(3:4)];
    measurement = [measurement, C*state + sqrt(R(1,1))*randn(1)];
    process_noise = [sqrt(Q(1,1))*randn(1);
                    sqrt(Q(2,2))*randn(1);
                    sqrt(Q(3,3))*randn(1);
                    sqrt(Q(4,4))*randn(1)];
    state = A*state + process_noise;   
end

Pm = P0;
[K] = vel_est_kalman_filt_test( A, C, Q, R, Pm);

 % run KF to the data:
 sem = [0, 0, 0, 0]';
 pose = [];
 vele_x = [];
% measurement step
for i = 1:length(pose_true)
    sep = sem + K*(measurement(:,i) - C*sem);
    pose = [pose, sep(1:2)];
    vele_x = [vele_x, sep(3:4)];
 % prediction step
    sem = A*sep; %+ B*vele; % pass this final value
end

% compare and plot kalman filter output
j = 1:length(pose);
figure(1)
plot(j, pose(1,:), 'b', j, pose_true(1,:), 'r')
legend('KF position x', 'true position x')
xlabel('sample 100')

figure(2)
plot(j, pose(2,:), 'b', j, pose_true(2,:), 'r')
legend('KF position y', 'true position y')
xlabel('sample 100')

figure(3)
plot(j, vele_x(1,:), 'b', j, veltrue(1,:), 'r')
legend('KF velocity x', 'true velocity x')
xlabel('sample 100')

figure(4)
plot(j, vele_x(2,:), 'b', j, veltrue(2,:), 'r')
legend('KF velocity y', 'true velocity y')
xlabel('sample 100')
     