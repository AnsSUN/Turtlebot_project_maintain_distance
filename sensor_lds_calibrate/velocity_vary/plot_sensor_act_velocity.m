clc, clear all, close all

% loading the data of the sensor measurements.

vrel_point05 = load('V_x_relsave_pt05.mat');
vrel_pt02 = load('V_x_relsave_pt02.mat');
vrel_pt2 = load('V_x_relsave_pt2.mat');
vrel_pt1 = load('V_x_relsave_pt1.mat');
vrel_pt2.V_x_rel_save   = vrel_pt2.V_x_rel_save(2: 8); % taking actual readings.

 % actual velocity
v_real_actualpt02 = 0.02 * ones(1, 7);
v_real_actualpt05 = 0.05*ones(1, 7);
v_real_actualpt2 = 0.2*ones(1, 7);
v_real_actualpt1 = 0.1*ones(1, 7);
% concatenate measured values into matrix:
v_measure_val = [vrel_pt02.V_x_rel_save(1:7), vrel_point05.V_x_rel_save(1:7), vrel_pt1.V_x_rel_save(1:7), vrel_pt2.V_x_rel_save(1:7)];
% concatenating the actual and measured values of the distance.


figure(1)
scatter(v_measure_val(1:7,1)', v_real_actualpt02)
hold on

scatter(v_measure_val(1:7,2)', v_real_actualpt05)
scatter(v_measure_val(1:7,3)', v_real_actualpt1)
scatter(v_measure_val(1:7,4)', v_real_actualpt2)
xlabel('Measured velocity')
ylabel('actual velocity')
title('graph of measured velocity vs actual velocity.')

hold off