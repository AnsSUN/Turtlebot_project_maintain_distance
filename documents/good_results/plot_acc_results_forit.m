clear all, close all, clc

const_dist = 0.4;
%% loading data for constant velocity 0.07 m/s with frame rate =16

ego_bot_vel_pt07_load = load('V_x_relsave_plot.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save;

%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;

%%% plotting the data for constant velocity 0.07m/s %%%
indx_pt07 = 1:length(ego_bot_vel_pt07);
%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_vel_pt07),1);
const_vel_plot = 0.06*ones(length(ego_bot_vel_pt07),1);

figure(1)

% ax(1) = subplot(2,1,1);
% plot(indx_pt07, error_dist_pt07, 'r', indx_pt07, zero_dist_plot, 'b')
% xlabel('Time')
% ylabel('Error (in m)')
% title('Error to maintain the distance between lead and ego vehicle (m)')
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:150), ego_bot_dist_pt07(1:150), 'r', indx_pt07(1:150), const_dist_plot(1:150), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m)')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:150), ego_bot_vel_pt07(1:150), 'r', indx_pt07(1:150), const_vel_plot(1:150), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead ego vehicle by ACC (m/s)')
hold off
