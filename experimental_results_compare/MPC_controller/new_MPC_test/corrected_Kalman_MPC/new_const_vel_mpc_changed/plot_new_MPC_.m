clear all, close all, clc

const_dist = 0.4;
%% loading data for constant velocity 0.07 m/s with MPC controller, all sensors frame rate =16

ego_bot_vel_pt07_load = load('V_x_relsave_plot_const_all.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot_const_all.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save(1,1:end);

%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;

%%% plotting the data for constant velocity 0.07m/s %%%
indx_pt07 = 1:length(ego_bot_vel_pt07);
%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_vel_pt07),1);

const_vel_plot = 0.07*ones(length(ego_bot_vel_pt07),1);
load('Sensor_speed_track_constant_vel');
const_vel_plot = lead_bot_vel_vari_const;

figure(1)
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:200), ego_bot_dist_pt07(1:200), 'r', indx_pt07(1:200), const_dist_plot(1:200), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m), all sensors')
legend('relative distance of lead and ego vehicle', 'constant relative distance to maintain = 0.4m')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:200), ego_bot_vel_pt07(1:200), 'r', indx_pt07(1:200), const_vel_plot(1:200), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead and ego vehicle by MPC controller (m/s), all sensors')
legend('velocity of ego vehicle', 'velocity of lead vehicle')
hold off

