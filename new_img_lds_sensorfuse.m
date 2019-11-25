obst_dis_threshold = 0.4;
veloc= 0.05;
robot = rospublisher('/cmd_vel') ;
velmsg = rosmessage(robot);
laser = rossubscriber('/scan');
odom_info = rossubscriber('/odom'); % check it to get the values!!
%% Calculating the normal distribution for Lidar detection over 120 degree.
%X = [-1 0 1];
X = [-60:1: 59];
norm = normpdf(X,0,20)*50; % Randommly taking sigma=20, change it after confirmation


if(ismember('/raspicam_node/image/compressed', rostopic('list')))
    imsub = rossubscriber('/raspicam_node/image/compressed');
    flag =1;
    load('use_for_turtlebot_detection.mat');
end
robvel = 0.0;  %Set robot speed command.
x_rel_save = [];
V_x_rel_save = [];
 while(flag)
    
     img = receive(imsub);
     img.Format = 'bgr8; jpeg compressed bgr8';
     I = readImage(img);
    
     %bboxes = detect(acfDetector, readImage(img));
     %I = insertObjectAnnotation(I,'rectangle',bboxes, 'Turtlebot');
     imshow(I);
     scan = receive(laser,3);
  %% Mimicing 120 degree angle for radar sensor
     velmsg = rosmessage(robot);
%      scan.Ranges(61:300) = 0; % for only 120 degree rance others are 0.
     scan.Ranges(31:330) = 0; % for only 60 degree rance others are 0.
     %% multiplying scan ranges with normal distribution normal distribution
%      new_lds(1) = norm(1)'.*scan.Ranges(1);
%      new_lds(2:3) = norm(2:3)'.*flip(scan.Ranges(1:2));
%      new_lds(1:60) = norm(1:60)'.*scan.Ranges(1:60);
%      new_lds(61:120) = norm(61:120)'.*flip(scan.Ranges(1:60));
% % % %      new_lds(1:60) = flip(scan.Ranges(1:60)); this is the main
% % % %      new_lds(61:120) = flip(scan.Ranges(301:360)); main
     new_lds(1:30) = flip(scan.Ranges(1:30)); 
     new_lds(31:60) = flip(scan.Ranges(331:360));
     lds_coord = lds_convert(new_lds');% Calculating the coordinates of the detected objects.
     lds_detect_vel = lds_vel_cal(lds_coord);
     
     % gaussian weights are added to the detections!!
     %lds_coord_gauss = norm'.*lds_coord;
     %lds_detect_vel_gauss = norm'.*lds_detect_vel;
     %vision_measurements = image_toworld_coord_test(365.952159941607);   % change this value to lds value which is at 0 degree!!
     
     % condition when velocity of object is not zero
     % do all algorithm stuff inside this if statement!!
      if any(lds_detect_vel(:, 1:2) ~= 0.0)% & vision_measurements ~= 0) % condition when velocity of object is not zero
           % concatenation for measurement of form [x, y, vx, vy]
          Measurement_lds = [lds_coord(lds_coord(:, 1)~=0, :), lds_detect_vel(lds_coord(:, 1)~=0, :)]; % adding only non zeroes values, after coordinate calculation   
          %save('turtlebot_lds_detect_data.mat','Measurement_lds');
          % passing measurement values to clustering algorithm
          num_point = size(Measurement_lds);
          for det = 1: num_point(1, 1)
            sensors{det, 1} = struct('SensorIndex', 1, 'Measurement', Measurement_lds(det, :)', 'ObjectClassID', 1);
          end
          detections = [sensors{:, 1}];
          vehicleLength = 0.20;
          detectionClusters = cluster_check_lds(detections, vehicleLength);
          %Measurement_vis = vision_measurements; % add it or pass this
          %detection to sensor fusion.
          x_rel_save = [x_rel_save; detectionClusters{1, 1}.Measurement(1, :)]; % collecting sensor data for calibration
          
          V_x_rel_save = [V_x_rel_save; detectionClusters{1, 1}.Measurement(3, :)];% collecting sensor data for calibration
          %save('V_x_relsave_pt2.mat', 'V_x_rel_save');
          % Velocity is not exactly correct as there are different
          % measurements from laser sensor at each point of time therefore,
          % it is in the form [x; y; vx; vy]
          % subscribe to odometery rostopic to get the current velocity of the vehicle
          %there is a slight change in the velocity for odometery model
          % might be because of covariance noise ordistribution between x
          % and y velocity of the odometery model.
          %acc_vel = ACC_test(detectionClusters{1, 1}.Measurement(3, :), detectionClusters{1, 1}.Measurement(4, :), detectionClusters{1, 1}.Measurement(1, :), detectionClusters{1, 1}.Measurement(2, :), odom_info.LatestMessage.Twist.Twist.Linear.X, odom_info.LatestMessage.Twist.Twist.Linear.Y);
          %velmsg.Linear.X = robvel + detectionClusters{1, 1}.Measurement(3, :);
          %send(robot,velmsg); 
       %%%%%%%%%%%%%%%%% uncomment from here after test the camera 
       %{
          acc_vel = acc_mpc_test(detectionClusters{1, 1}.Measurement(3, :), detectionClusters{1, 1}.Measurement(4, :), detectionClusters{1, 1}.Measurement(1, :), detectionClusters{1, 1}.Measurement(2, :), odom_info.LatestMessage.Twist.Twist.Linear.X, odom_info.LatestMessage.Twist.Twist.Linear.Y);
          if (acc_vel < 0.22 && acc_vel >= 0) % maximum velocity handle by the turtlebot burger motor
            velmsg.Linear.X = acc_vel;
            send(robot,velmsg);           
            robvel = acc_vel;
          end
          disp(['## -- Robot Velocity :',num2str(robvel)])
       %}
          % you can take some tolerance for velocity measurement to keep.
          clear lds_vel_cal; %clearing the persistent variable data write your process after this!!
    %%%%%%%%%%%%%%%%%%% uncomment this after test the camera
    %{
          if (acc_vel~=0)
              clear lds_vel_cal;
          end
    %}
%           if (dt~=0) % to clear the dt value in the mpc_acc_trst algo.
%               clear acc_mpc_test;
%           end

          %clear image_toworld_coord_test;          
          %clear Measurement; %keep this measurement line in last 
      end
     %save('x_relsave_pt2.mat', 'x_rel_save');
     
     velmsg.Linear.X = 0.00;
     send(robot,velmsg);     
     
    %bboxes = [bboxes, 0, 0, 0]; % change the values when velocities are calculated
    %confirmedTracks = sensor_fusion_turtlebot_test(scan, Measurement_vis', t.Sec);
 end
 