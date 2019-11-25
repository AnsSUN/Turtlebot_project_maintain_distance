%start rosinit('172.25.116.175') and then bringup the sensors of the turtlebot before running
%this code
obst_dis_threshold = 0.2;
veloc= 0.05;
robot = rospublisher('/cmd_vel') ;
velmsg = rosmessage(robot);
laser = rossubscriber('/scan');
t = rostime('now');
tic;
while(1) %toc < 100
  scan = receive(laser,3);
  %% Mimicing 120 degree angle for radar sensor
  velmsg = rosmessage(robot);
  scan.Ranges(61:300) = 0; % for only 120 degree rance others are 0.
  %laser_rad_mimc0_60 = scan.Ranges(1:60);
  %laser_rad_mimc300_360 = scan.Ranges(301:360);
  %scan_cat = [laser_rad_mimc0_60; laser_rad_mimc300_360];
  idx_keep = find(scan.Ranges > 0);
  scan_cat = scan.Ranges(idx_keep);
  find_min = min(scan_cat);
  if (find_min > obst_dis_threshold)
      velmsg.Linear.X = veloc;
      send(robot,velmsg);
  else
      velmsg.Linear.X = 0;
      send(robot,velmsg);
  end
  save('turtlebot_scan_data.mat','scan')
  plot(scan);
end
%print("laser_rad_mimc: ", laser_rad_mimc)
%save('turtlebot_scan_data.mat','scan')
clear 
