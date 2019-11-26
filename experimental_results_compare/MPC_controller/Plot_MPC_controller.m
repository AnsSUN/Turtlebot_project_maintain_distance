clear all, close all, clc

const_dist = 0.4;
%% loading data for constant velocity 0.07 m/s with MPC controller, all sensors frame rate =5

ego_bot_vel_pt07_load = load('V_x_relsave_plot_all_check2.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot_all_check2.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save(1,1:end);

%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;

%%% plotting the data for constant velocity 0.07m/s %%%
indx_pt07 = 1:length(ego_bot_vel_pt07);
%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_vel_pt07),1);
const_vel_plot = 0.07*ones(length(ego_bot_vel_pt07),1);

figure(1)
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:135), ego_bot_dist_pt07(1:135), 'r', indx_pt07(1:135), const_dist_plot(1:135), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m), all sensors')
legend('relative distance of lead and ego vehicle', 'constant relative distance to maintain = 0.4m')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:135), ego_bot_vel_pt07(1:135), 'r', indx_pt07(1:135), const_vel_plot(1:135), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead and ego vehicle by MPC controller (m/s), all sensors')
legend('velocity of ego vehicle', 'velocity of lead vehicle')
hold off

%% loading data for constant velocity 0.07 m/s with MPC controller, LDS sensors frame rate =5

ego_bot_vel_pt07_load = load('V_x_relsave_plot_LDS.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot_LDS.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save(1,1:end);

%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;

%%% plotting the data for constant velocity 0.07m/s %%%
indx_pt07 = 1:length(ego_bot_vel_pt07);
%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_vel_pt07),1);
const_vel_plot = 0.07*ones(length(ego_bot_vel_pt07),1);

figure(2)
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:150), ego_bot_dist_pt07(1:150), 'r', indx_pt07(1:150), const_dist_plot(1:150), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m), LDS sensors')
legend('relative distance of lead and ego vehicle', 'constant relative distance to maintain = 0.4m')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:150), ego_bot_vel_pt07(1:150), 'r', indx_pt07(1:150), const_vel_plot(1:150), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead and ego vehicle by MPC controller (m/s), LDS sensors')
legend('velocity of ego vehicle', 'velocity of lead vehicle')
hold off


%% loading data for constant velocity 0.07 m/s with MPC controller, camera sensors frame rate =05

ego_bot_vel_pt07_load = load('V_x_relsave_plot_camera.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot_camera.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save;

%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;

%%% plotting the data for constant velocity 0.07m/s %%%
indx_pt07 = 1:length(ego_bot_vel_pt07);
%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_vel_pt07),1);
const_vel_plot = 0.07*ones(length(ego_bot_vel_pt07),1);

figure(3)
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:150), ego_bot_dist_pt07(1:150), 'r', indx_pt07(1:150), const_dist_plot(1:150), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m), camera sensors')
legend('relative distance of lead and ego vehicle', 'constant relative distance to maintain = 0.4m')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:150), ego_bot_vel_pt07(1:150), 'r', indx_pt07(1:150), const_vel_plot(1:150), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead and ego vehicle by MPC controller (m/s), camera sensors')
legend('velocity of ego vehicle', 'velocity of lead vehicle')
hold off

%% loading data for variable velocity with MPC controller, all sensors frame rate =5

ego_bot_vel_pt07_load = load('step_V_x_relsave_plot_all.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('step_x_relsave_plot_all.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save(1,1:end);

%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;
lead_vel_vari = rosbag('test_rosbag_variable_vel.bag');
lead_vel_vari_select = select(lead_vel_vari,'Topic','/cmd_vel');
msgStructs = readMessages(lead_vel_vari_select,'DataFormat','struct');
lead_bot_vel_vari =[];
for i = 1:2:length(msgStructs)
    lead_bot_vel_vari = [lead_bot_vel_vari, msgStructs{i, 1}.Linear.X];
end

%const_dist_plot = const_dist*ones(length(ego_bot_dist_vari),1);
%const_vel_plot = 0.07*ones(length(lead_bot_vel_vari),1);
shift_arry_7_ele = 0.1*ones(1,49);
lead_bot_vel_vari = [shift_arry_7_ele, lead_bot_vel_vari(1:end-1)];
indx_pt07 = 1:length(lead_bot_vel_vari);


figure(4)
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:120), ego_bot_dist_pt07(1:120), 'r', indx_pt07(1:120), const_dist_plot(1:120), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m), all sensors')
legend('relative distance of lead and ego vehicle', 'constant relative distance to maintain = 0.4m')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:120), ego_bot_vel_pt07(1:120), 'r', indx_pt07(1:120), lead_bot_vel_vari(1:120), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' step velocity of lead and ego vehicle by MPC controller (m/s), all sensors')
legend('velocity of ego vehicle', 'velocity of lead vehicle')
hold off
