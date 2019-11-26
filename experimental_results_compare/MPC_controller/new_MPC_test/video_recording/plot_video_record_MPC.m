%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;
clear all, close all, clc

const_dist = 0.4;

%% loading data for variable velocity with MPC controller, all sensors frame rate =16

ego_bot_vel_pt07_load = load('V_x_relsave_plot_all_step.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot_all_step.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save(1,1:end);

lead_vel_vari = rosbag('test_rosbag_variable_vel.bag');
lead_vel_vari_select = select(lead_vel_vari,'Topic','/cmd_vel');
msgStructs = readMessages(lead_vel_vari_select,'DataFormat','struct');
lead_bot_vel_vari =[];
for i = 1:2:length(msgStructs)
    lead_bot_vel_vari = [lead_bot_vel_vari, msgStructs{i, 1}.Linear.X];
end

const_dist_plot = const_dist*ones(length(ego_bot_dist_pt07),1);
const_vel_plot = 0.2*ones(length(lead_bot_vel_vari),1);
shift_arry_7_ele = 0.1*ones(1,15);
lead_bot_vel_vari = [shift_arry_7_ele, lead_bot_vel_vari];
lead_bot_vel_vari = [lead_bot_vel_vari, const_vel_plot'];
indx_pt07 = 1:length(lead_bot_vel_vari);


figure(1)
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:147), ego_bot_dist_pt07(1:147), 'r', indx_pt07(1:147), const_dist_plot(1:147), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m), all sensors')
legend('relative distance of lead and ego vehicle', 'constant relative distance to maintain = 0.4m')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:147), ego_bot_vel_pt07(1:147), 'r', indx_pt07(1:147), lead_bot_vel_vari(1:147), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' step velocity of lead and ego vehicle by MPC controller (m/s), all sensors')
legend('velocity of ego vehicle', 'velocity of lead vehicle')
hold off
