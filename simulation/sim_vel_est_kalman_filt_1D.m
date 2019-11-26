% This code has referred from
% https://www.cs.cmu.edu/~cga/dynopt/kalman/kalman.html and
% https://statweb.stanford.edu/~candes/acm116/Handouts/Kalman.pdf
% for more info check it out.
% as we are having longitudinal autonomy, therefore taking simple state transition matrix!!
function K  = sim_vel_est_kalman_filt_1D(A, C, Q, R, Pm)
%{
    C = [1, 0];
R = [0.000225];
Q = [0.0001, 0;
      0, 0.0001];
P0 = [0.0001, 0;
       0, 0.0001];
    
sem = [0, 0]';
          if detectionClusters{1, 1}.Measurement(1, :) >= 0.5
            Q = [(0.035 * detectionClusters{1, 1}.Measurement(1, :))^2, 0;
                    0,  (0.035 * detectionClusters{1, 1}.Measurement(1, :))^2];
          end
          if detectionClusters{1, 1}.Measurement(1, :) >= 0.5
                R = [(0.05*detectionClusters{1, 1}.Measurement(1, :))^2];
          end
          if detectionClusters{1, 1}.Measurement(1, :) >= 0.5
                P0 = [(0.035 * detectionClusters{1, 1}.Measurement(1, :))^2, 0;
                        0 , (0.035 * detectionClusters{1, 1}.Measurement(1, :))^2];
          end
          dt = toc(tStart);
          tStart = tic;
          A = [1, dt;
                0, 1];
%}
% designing the Kalman filter

for i = 1:1000
% measurement step

    S = C * Pm * C' + R;
    %K = Pm*C'*inv(S); % change this inverse thing to solve with solutions of linear equations.
    % changing to linear eq solution:
    K =  Pm*C' * inv(S); % as it is 1 D dividing it, but for matrix linsolve is the best to get the "K".

    Pp = Pm - K*C*Pm;
 % prediction step
    Pm = A*Pp*A' + Q;
end

 
end