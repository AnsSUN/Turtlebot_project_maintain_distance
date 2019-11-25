clc, clear all, close all

% loading the data of the sensor measurements.

xrel_point5 = load('x_relsave_1by2.mat');
xrel_one_m = load('x_relsave_1m.mat');
xrel_two_m = load('x_relsave_2m.mat');
xrel_three_m = load('x_relsave_3m.mat');

x_rel_meas = [0.5, 1, 2, 3]; % actual distance
x_reel_actualpt5 = 0.5 * ones(1, 10);
x_reel_actualone_m = ones(1, 10);
x_reel_actualtwo_m = 2*ones(1, 10);
x_reel_actualthree_m = 3*ones(1, 10);
% concatenate measured values into matrix:
x_measure_val = [xrel_point5.x_rel_save(1:10), xrel_one_m.x_rel_save(1:10), xrel_two_m.x_rel_save(1:10), xrel_three_m.x_rel_save(1:10)];
% concatenating the actual and measured values of the distance.
x_plot_val = [x_rel_meas; x_measure_val];

figure(1)
scatter(x_measure_val(1:10,1)', x_reel_actualpt5)
figure()
hold on

scatter(x_measure_val(1:10,2)', x_reel_actualone_m)
scatter(x_measure_val(1:10,3)', x_reel_actualtwo_m)
scatter(x_measure_val(1:10,4)', x_reel_actualthree_m)
xlabel('Measured distance')
ylabel('actual distance')
title('graph of measured distance vs actual distance.')

hold off

%% calculating teh frequency of the measurement to calculate the sensor noise.

Y = round(xrel_point5.x_rel_save,3);
a = unique(Y);
out = [a,histc(Y(:),a)];
data = Y;
gauss_fit_data = fitdist(data,'Normal');
x_pt5m = [0.5130:.0001: 0.5234];
gauss_fit = normpdf(x_pt5m, 0.518222, 0.00130859);
% x_onem = [0.9969:.0001: 1.0161];
% gauss_fit = normpdf(x_onem, 1.00651, 0.00320917);
%% Conclusion add sigma value 3 percent of the mean measurement.
figure()
hold on
bar(out(:, 1), out(:,end));
plot(x_pt5m,gauss_fit)
