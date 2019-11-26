%clear all, close all, clc

%% constant velocity = 0.07 m/s is recorded on track through odom rostopic actual time of recors is 99.1749 and time step is T = 0.0333
% as the experiment has time step T = 0.4, therefore saving the data of
% after about each 12 data record.

lead_vel_vari = rosbag('const_vel_track_record.bag');
lead_vel_vari_select = select(lead_vel_vari,'Topic','/odom');
msgStructs = readMessages(lead_vel_vari_select,'DataFormat','struct');
lead_bot_vel_vari_const =[];
for i = 1:12:length(msgStructs)
    lead_bot_vel_vari_const = [lead_bot_vel_vari_const, msgStructs{i, 1}.Twist.Twist.Linear.X];
end

%% constant velocity = 0.07 m/s is recorded on track through odom rostopic actual time of recors is 56.8305 and time step is T = 0.0333
% as the experiment has time step T = 0.4, therefore saving the data of
% after about each 12 data record.

lead_vel_vari = rosbag('step_vel_track_record.bag');
lead_vel_vari_select = select(lead_vel_vari,'Topic','/odom');
msgStructs = readMessages(lead_vel_vari_select,'DataFormat','struct');
lead_bot_vel_vari =[];
for i = 1:12:length(msgStructs)
    lead_bot_vel_vari = [lead_bot_vel_vari, msgStructs{i, 1}.Twist.Twist.Linear.X];
end