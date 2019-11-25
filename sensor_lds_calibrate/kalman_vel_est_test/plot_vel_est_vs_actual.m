clear all, close all, clc

V_xrel_pt1 = load('V_x_relsave_pt1.mat');
V_xrel_pt02 = load('V_x_relsave_pt02.mat');
V_xrel_pt2 = load('V_x_relsave_pt2.mat');
V_xrel_pt05 = load('V_x_relsave_pt05.mat');

V_xrel_pt1_act = 0.1 * ones(15,1);
V_xrel_pt02_act = 0.02 * ones(15,1);
V_xrel_pt2_act = 0.2 * ones(15,1);
V_xrel_pt05_act = 0.05 * ones(15,1);

scatter(-V_xrel_pt1.V_x_rel_save(15:29), V_xrel_pt1_act)
hold on
scatter(-V_xrel_pt02.V_x_rel_save(51:65), V_xrel_pt02_act)
scatter(-V_xrel_pt2.V_x_rel_save(5:19), V_xrel_pt2_act)
scatter(-V_xrel_pt05.V_x_rel_save(6:20), V_xrel_pt05_act)

xlabel('measured velocity')
ylabel('actual velocity')
title('kalman filter estimate velocity')
hold off