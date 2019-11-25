clear all, close all, clc

x_rel_1m =load('vis_x_relsave_1m.mat');
x_rel_1pt5 = load('vis_x_relsave_1pt5.mat');
x_rel_2m = load('vis_x_relsave_2m.mat');
x_rel_pt35 = load('vis_x_relsave_pt35.mat');
x_rel_pt72 = load('vis_x_relsave_pt72.mat');

x_act_1m = ones(23,1);
x_act_1pt5 = 1.5*ones(23,1);
x_act_2m = 2*ones(23,1);
x_act_pt35 = 0.35 * ones(23,1);
x_act_pt72 = 0.72*ones(23,1);

scatter(x_rel_1m.vis_x_rel_save(1:23), x_act_1m)
hold on
scatter(x_rel_1pt5.vis_x_rel_save(1:23), x_act_1pt5)
scatter(x_rel_2m.vis_x_rel_save(1:23), x_act_2m)
scatter(x_rel_pt35.vis_x_rel_save(1:23), x_act_pt35)
scatter(x_rel_pt72.vis_x_rel_save(1:23), x_act_pt72)
xlabel('measured distance')
ylabel('actual distance')
title('distance estimation through camera vs actual distance')
hold off

%% calculating the frequency of the measurement to calculate the sensor noise.
% taking SNR = 19 after calculation 

Y = round(x_rel_1pt5.vis_x_rel_save,3);
a = unique(Y);
out = [a,histc(Y(:),a)];
data = Y;
gauss_fit_data = fitdist(data,'Normal');
%x_pt72m = [-1:.0001: 1]; %  actual relarive distance = 0.72 
%gauss_fit_pt72 = normpdf(x_pt5m, 0.625225, 0.0315404); SNR = mu/sigma = 19.8230
x_pt5m = [0.5130:.0001: 0.5234];
gauss_fit = normpdf(x_pt5m, 1.36969 , 0.0763855); % SNR = mu/sigma = 17.9313
