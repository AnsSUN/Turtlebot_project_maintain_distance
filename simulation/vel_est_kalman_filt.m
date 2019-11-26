% This code has referred from
% https://www.cs.cmu.edu/~cga/dynopt/kalman/kalman.html and
% https://statweb.stanford.edu/~candes/acm116/Handouts/Kalman.pdf
% for more info check it out.
% as we are having longitudinal autonomy, therefore taking simple state transition matrix!!
function [K] = vel_est_kalman_filt(A, C, Q, R, Pm)

 % copy this data A, B ,C to outside of this function and also Q, R, P0 

% designing the Kalman filter

% measurement step

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
 
 


