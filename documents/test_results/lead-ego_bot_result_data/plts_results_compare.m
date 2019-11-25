clear all, close all, clc

const_dist = 0.4;
%% loading data for constant velocity 0.07 m/s with frame rate =16

lead_vel_pt07 = rosbag('test_rosbag_const_vel_pt07.bag');
lead_vel_pt07_select = select(lead_vel_pt07,'Topic','/cmd_vel');
msgStructs = readMessages(lead_vel_pt07_select,'DataFormat','struct');
lead_bot_vel_07 =[];
for i = 1:2:length(msgStructs)
    lead_bot_vel_07 = [lead_bot_vel_07, msgStructs{i, 1}.Linear.X];
end
ego_bot_vel_pt07_load = load('V_x_relsave_plot_const_vel_pt07.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot_const_vel_pt07.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save;

%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;

%%% plotting the data for constant velocity 0.07m/s %%%
indx_pt07 = 1:length(ego_bot_vel_pt07);
%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_vel_pt07),1);
const_vel_plot = 0.07*ones(length(ego_bot_vel_pt07),1);

figure(1)

% ax(1) = subplot(2,1,1);
% plot(indx_pt07, error_dist_pt07, 'r', indx_pt07, zero_dist_plot, 'b')
% xlabel('Time')
% ylabel('Error (in m)')
% title('Error to maintain the distance between lead and ego vehicle (m)')
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:169), ego_bot_dist_pt07(1:169), 'r', indx_pt07(1:169), const_dist_plot(1:169), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m)')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:169), ego_bot_vel_pt07(1:169), 'r', indx_pt07(1:169), const_vel_plot(1:169), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead ego vehicle by ACC (m/s)')
hold off

%% loading data for constant velocity 0.07 m/s with frame rate =5

lead_vel_pt07 = rosbag('test_rosbag_const_vel_pt07_framerate5.bag');
lead_vel_pt07_select = select(lead_vel_pt07,'Topic','/cmd_vel');
msgStructs = readMessages(lead_vel_pt07_select,'DataFormat','struct');
lead_bot_vel_07 =[];
for i = 1:2:length(msgStructs)
    lead_bot_vel_07 = [lead_bot_vel_07, msgStructs{i, 1}.Linear.X];
end
ego_bot_vel_pt07_load = load('V_x_relsave_plot_const_vel_pt07_framerate5.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot_const_vel_pt07_framerate5.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save;

%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;

%%% plotting the data for constant velocity 0.07m/s %%%
indx_pt07 = 1:length(ego_bot_vel_pt07);
%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_vel_pt07),1);
const_vel_plot = 0.07*ones(length(ego_bot_vel_pt07),1);

figure(2)

% ax(1) = subplot(2,1,1);
% plot(indx_pt07, error_dist_pt07, 'r', indx_pt07, zero_dist_plot, 'b')
% xlabel('Time')
% ylabel('Error (in m)')
% title('Error to maintain the distance between lead and ego vehicle (m)')
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:131), ego_bot_dist_pt07(1:131), 'r', indx_pt07(1:131), const_dist_plot(1:131), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m) frame rate = 5')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:131), ego_bot_vel_pt07(1:131), 'r', indx_pt07(1:131), const_vel_plot(1:131), 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead ego vehicle by ACC (m/s) frame rate = 5')
hold off

%% loading data for variable velocity with frame rate =16
lead_vel_vari = rosbag('test_rosbag_variable_vel.bag');
lead_vel_vari_select = select(lead_vel_vari,'Topic','/cmd_vel');
msgStructs = readMessages(lead_vel_vari_select,'DataFormat','struct');
lead_bot_vel_vari =[];
for i = 1:2:length(msgStructs)
    lead_bot_vel_vari = [lead_bot_vel_vari, msgStructs{i, 1}.Linear.X];
end
ego_bot_vel_vari_load = load('V_x_relsave_plot_variable_vel.mat');
ego_bot_vel_vari = ego_bot_vel_vari_load.V_x_rel_save;
ego_bot_dist_vari_load = load('x_relsave_plot_variable_vel.mat');
ego_bot_dist_vari = ego_bot_dist_vari_load.x_rel_save;

%%% plotting the data for variable velocity %%%

%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_dist_vari),1);
%const_vel_plot = 0.07*ones(length(lead_bot_vel_vari),1);
shift_arry_7_ele = 0.1*ones(1,7);
lead_bot_vel_vari = [shift_arry_7_ele, lead_bot_vel_vari(1:end-1)];
indx_pt07 = 1:length(lead_bot_vel_vari);
figure(3)

% ax(1) = subplot(2,1,1);
% plot(indx_pt07, error_dist_pt07, 'r', indx_pt07, zero_dist_plot, 'b')
% xlabel('Time')
% ylabel('Error (in m)')
% title('Error to maintain the distance between lead and ego vehicle (m)')
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:105), ego_bot_dist_vari(1:105), 'r', indx_pt07(1:105), const_dist_plot(1:105), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m)')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:105), ego_bot_vel_vari(1:105), 'r', indx_pt07(1:105), lead_bot_vel_vari(1:105)', 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead ego vehicle by ACC (m/s) constraint = max velocity is 0.15')
hold off

%% loading data for manual variable velocity with frame rate =5

lead_vel_vari = rosbag('test_rosbag_variable_vel_framerate5_new_manual.bag');
lead_vel_vari_select = select(lead_vel_vari,'Topic','/cmd_vel');
msgStructs = readMessages(lead_vel_vari_select,'DataFormat','struct');
lead_bot_vel_vari =[];
for i = 1:4:length(msgStructs)
    lead_bot_vel_vari = [lead_bot_vel_vari, msgStructs{i, 1}.Linear.X];
end
ego_bot_vel_vari_load = load('V_x_relsave_plot_variable_vel_framerate5_manual_new.mat');
ego_bot_vel_vari = ego_bot_vel_vari_load.V_x_rel_save;
ego_bot_dist_vari_load = load('x_relsave_plot_variable_vel_framerate5_manual_new.mat');
ego_bot_dist_vari = ego_bot_dist_vari_load.x_rel_save;

%%% plotting the data for variable velocity  %%%

%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_dist_vari),1);
%const_vel_plot = 0.07*ones(length(lead_bot_vel_vari),1);
lead_bot_vel_vari(1:3) = [];
lead_bot_vel_vari(58:59) = [];
%lead_bot_vel_vari = [shift_arry_7_ele, lead_bot_vel_vari(1:end-1)];
indx_pt07 = 1:length(ego_bot_dist_vari);
figure(4)

% ax(1) = subplot(2,1,1);
% plot(indx_pt07, error_dist_pt07, 'r', indx_pt07, zero_dist_plot, 'b')
% xlabel('Time')
% ylabel('Error (in m)')
% title('Error to maintain the distance between lead and ego vehicle (m)')
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:110), ego_bot_dist_vari(1:110), 'r', indx_pt07(1:110), const_dist_plot(1:110), 'b')
xlabel('Time')
ylabel('distance (in m)')
title(' distance(measured by sensor) between lead and ego vehicle (m) frame rate = 5')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:110), ego_bot_vel_vari(1:110), 'r', indx_pt07(1:110), lead_bot_vel_vari(1:110)', 'b')
xlabel('Time')
ylabel('velocity (in m/s)')
title(' velocity of lead ego vehicle by ACC (m/s) frame rate = 5')
hold off

%% loading data for constant velocity 0.07 m/s with frame rate =5 comparind odometery info and acc velocity

lead_vel_pt07 = rosbag('test_rosbag_const_vel_pt07_framerate5.bag');
lead_vel_pt07_select = select(lead_vel_pt07,'Topic','/cmd_vel');
msgStructs = readMessages(lead_vel_pt07_select,'DataFormat','struct');
lead_bot_vel_07 =[];
for i = 1:2:length(msgStructs)
    lead_bot_vel_07 = [lead_bot_vel_07, msgStructs{i, 1}.Linear.X];
end
ego_bot_act_vel_pt07_load = load('V_x_rel_actual_odom_save_plot_const_pt07.mat');
ego_bot_act_vel_pt07 = ego_bot_act_vel_pt07_load.V_x_rel_odom;
ego_bot_vel_pt07_load = load('V_x_relsave_plot_odom_test_const_pt07.mat');
ego_bot_vel_pt07 = ego_bot_vel_pt07_load.V_x_rel_save;
ego_bot_dist_pt07_load = load('x_relsave_plot_odom_test_const_pt07.mat');
ego_bot_dist_pt07 = ego_bot_dist_pt07_load.x_rel_save;

%error_dist_pt07 = ego_bot_dist_pt07 - const_dist;

%%% plotting the data for constant velocity 0.07m/s %%%
indx_pt07 = 1:length(ego_bot_vel_pt07);
%zero_dist_plot = zeros(length(ego_bot_vel_pt07),1);
const_dist_plot = const_dist*ones(length(ego_bot_vel_pt07),1);
const_vel_plot = 0.07*ones(length(ego_bot_vel_pt07),1);
ego_bot_act_vel_pt07(1:2) = [];
figure(5)

% ax(1) = subplot(2,1,1);
% plot(indx_pt07, error_dist_pt07, 'r', indx_pt07, zero_dist_plot, 'b')
% xlabel('Time')
% ylabel('Error (in m)')
% title('Error to maintain the distance between lead and ego vehicle (m)')
hold on
ax(1) = subplot(2,1,1);
plot(indx_pt07(1:142), ego_bot_dist_pt07(1:142), 'r', indx_pt07(1:142), const_dist_plot(1:142), 'b')
xlabel('Time')
ylabel('distance (in m)')
title('distance(measured by sensor) between lead and ego vehicle (m) frame rate = 5')
ax(2) = subplot(2,1,2);
plot(indx_pt07(1:142), ego_bot_vel_pt07(1:142), 'r', indx_pt07(1:142), const_vel_plot(1:142), 'b', indx_pt07(1:142), ego_bot_act_vel_pt07(1:142))
%plot(indx_pt07(1:142), ego_bot_act_vel_pt07(1:142))
xlabel('Time')
ylabel('velocity (in m/s)')
legend('velocity by ACC', 'constant velocity of lead =0.07 m/s', 'odometry velocity')
title(' velocity of lead ego vehicle by ACC (m/s) frame rate = 5')
hold off
