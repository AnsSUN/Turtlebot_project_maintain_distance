function [x_kal_vis, y_kal_vis] = run_kalman_vision(x_est_vis, y_est_vis, sem)
 A = [1, 0;
      0, 1];
 C = [1, 0;
     0, 1];
R = [0.01];
Q = [0.01, 0;
      0, 0.01];
P0 = [0.01, 0;
       0, 0.01];
    
%sem = [0, 0, 0, 0]'; 
Pm = P0;
[K] = vel_est_kalman_filt( A, C, Q, R, Pm);
sep = sem + K*([x_est_vis; y_est_vis] - C*sem);
x_kal_vis = sep(1);
y_kal_vis = sep(2);
%velex = [sep(3:4)];
          % prediction step
sem = A*sep; %+ B*vele; % pass this final value
end