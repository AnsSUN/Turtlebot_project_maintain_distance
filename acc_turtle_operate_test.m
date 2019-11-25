%% main file to execute different control algorithms
% make sure to initialize the ros master node by "rosinit" before executing it.

robot = rospublisher('/cmd_vel') ;
velmsg = rosmessage(robot);
laser = rossubscriber('/scan');
odom_info = rossubscriber('/odom'); 

if(ismember('/raspicam_node/image/compressed', rostopic('list')))
    imsub = rossubscriber('/raspicam_node/image/compressed');
    flag =1;
    load('use_for_turtlebot_detection.mat');
end

X = [-60:1: 59];
robvel = 0.0;  %Set robot speed command.


C = [1, 0, 0, 0;
     0, 1, 0, 0];
%R = [0.000225]; %old value
R = [0.0041];
Q = [0.0001, 0, 0, 0;
      0, 0.0001, 0, 0;
      0, 0, 0.0001, 0;
      0, 0, 0, 0.0001];
P0 = [0.0001, 0, 0, 0;
       0, 0.0001, 0, 0;
        0, 0, 0.0001, 0
        0, 0, 0, 0.0001];
    
sem = [0, 0, 0, 0]'; 

sem_vis = [0, 0]';
V_x_rel_save = [];
v_kalman_save = [];
V_x_rel_odom = [];
x_rel_save = [];
tStart = tic; 
Measurement_vis =[0,0];
detection_meas =[];
lds_mean_measurement_save = [];
vis_measurement_mean_save = [];
 while(flag)
     msg_odom = receive(odom_info);
     V_x_rel_odom = [V_x_rel_odom; msg_odom.Twist.Twist.Linear.X];
     save('V_x_rel_odom_save_plot.mat', 'V_x_rel_odom');
     img = receive(imsub);
     img.Format = 'bgr8; jpeg compressed bgr8';
     I = readImage(img);
    
     bboxes = detect(acfDetector, readImage(img));
     if ~isempty(bboxes)
        vis_xrel = plot_pix_vs_dist(bboxes(3));
        y_vis = y_coord_estimation_vision_410X308((bboxes(1)+(bboxes(3)/2)), vis_xrel);
        
        Measurement_vis = [vis_xrel, y_vis]; 
        %disp(['##1 -- vision distance : ',num2str(Measurement_vis)])
        vis_measurement_mean_save = [vis_measurement_mean_save; Measurement_vis];
     end
     I = insertObjectAnnotation(I,'rectangle',bboxes, 'Turtlebot');
     imshow(I);
     scan = receive(laser,3);
  %% Mimicing 30 degree angle for radar sensor
     velmsg = rosmessage(robot);
     scan.Ranges(16:345) = 0; % for only 30 degree range others are 0.

     new_lds(1:15) = flip(scan.Ranges(1:15)); 
     new_lds(16:30) = flip(scan.Ranges(346:360)); 

     lds_coord = lds_convert(new_lds');% Calculating the coordinates of the detected objects.
     
           % concatenation for measurement of form [x, y]
          Measurement_lds = [lds_coord(lds_coord(:, 1)~=0, :)]; % adding only non zeroes values, after coordinate calculation
          Measurement_lds = Measurement_lds -[0.1, 0]; % compensating the 10 cm distance
          lds_measurement_mean = mean(Measurement_lds,1); 
          lds_mean_measurement_save=[lds_mean_measurement_save; lds_measurement_mean];
          %save('turtlebot_lds_detect_data.mat','Measurement_lds');
          % passing measurement values to clustering algorithm
          if exist('Measurement_lds','var') == 1
              num_point = size(Measurement_lds);
          else
              num_point=1;
          end
          if num_point(1,1) ~=1
            for det = 1: num_point(1, 1)
                sensors{det, 1} = struct('SensorIndex', 1, 'Measurement', Measurement_lds(det, :)', 'ObjectClassID', 1);
            end
          end
          if ~isempty(Measurement_vis)
              sensors{num_point(1,1)+1, 1} = struct('SensorIndex', 2, 'Measurement', Measurement_vis', 'ObjectClassID', 1);
          end
          if exist('sensors','var') == 1
              detections = [sensors{:, 1}];
          else
              detections= struct('SensorIndex', 1, 'Measurement', [0,0]', 'ObjectClassID', 1);
          end

          vehicleLength = 0.20;
          detectionClusters = cluster_lds_new(detections, vehicleLength);
          num_detect = size(detectionClusters);
          for i=1:num_detect
            detection_meas = [detection_meas, (detectionClusters{i, 1}.Measurement)]; 
          end

          mean_measurement = mean(detection_meas, 2); 
          %detection to sensor fusion.
          % creating noise parameters which depend on measurement:
          if detectionClusters{1, 1}.Measurement(1, :) >= 0.5
            Q = [(0.035 * detectionClusters{1, 1}.Measurement(1, :))^2, 0, 0, 0;
                    0, (0.035 * detectionClusters{1, 1}.Measurement(1, :))^2, 0, 0;
                    0, 0, (0.035 * detectionClusters{1, 1}.Measurement(1, :))^2, 0;
                    0, 0, 0, (0.035 * detectionClusters{1, 1}.Measurement(1, :))^2];
          end
          if detectionClusters{1, 1}.Measurement(1, :) >= 0.5
                R = [(0.05*detectionClusters{1, 1}.Measurement(1, :))^2];
          end
          if detectionClusters{1, 1}.Measurement(1, :) >= 0.5
                P0 = [(0.035 * detectionClusters{1, 1}.Measurement(1, :))^2, 0, 0, 0;
                        0, (0.035 * detectionClusters{1, 1}.Measurement(1, :))^2, 0, 0;
                        0 , 0, (0.035 * detectionClusters{1, 1}.Measurement(1, :))^2, 0;
                        0 , 0, 0, (0.035 * detectionClusters{1, 1}.Measurement(1, :))^2];
          end
          dt = toc(tStart);
          tStart = tic;
          A = [1, 0, dt, 0;
                0, 1, 0, dt;
                0, 0, 1, 0;
                 0, 0, 0, 1];
 
%           B = [0;
%                0;
%                dt;
%                dt];
           % applying kalman filter after clustering:
           Pm = P0;
          [K] = vel_est_kalman_filt( A, C, Q, R, Pm);
          sep = sem + K*(mean_measurement - C*sem);
          pose = [sep(1:2)];
          velex = [sep(3:4)];
          % prediction step
          sem = A*sep; %+ B*vele; % pass this final value
          
          % measurements from laser sensor at each point of time therefore,
          % it is in the form [x; y; vx; vy]
          % subscribe to odometery rostopic to get the current velocity of the vehicle
          %there is a slight change in the velocity for odometery model
          % might be because of covariance noise or distribution between x
          % and y velocity of the odometery model.

       % use function: "ACC_PI_test" for Proportional Integral Control
       % use function: "new_mpc_test" for Model Predictive Control
       % use function: "ACC_P_test" for Proportional Control

          acc_vel = ACC_PI_test(velex(1), velex(2), mean_measurement(1), mean_measurement(2), msg_odom.Twist.Twist.Linear.X, msg_odom.Twist.Twist.Linear.Y);

          if (acc_vel < 0.2 && acc_vel >= 0) % maximum velocity handle by the turtlebot burger motor
            velmsg.Linear.X = acc_vel;
            send(robot,velmsg);           
            robvel = 0;
          end
          
          v_kalman_save = [v_kalman_save; velex(1)];
          save('V_x_kalman_save_plot.mat', 'v_kalman_save');
          V_x_rel_save = [V_x_rel_save; robvel];
          %x_rel_save = [x_rel_save, mean_measurement];
          x_rel_save = [x_rel_save, mean_measurement];
          save('V_x_relsave_plot.mat', 'V_x_rel_save');
          save('x_relsave_plot.mat', 'x_rel_save');
          %disp(['## -- Robot Velocity :',num2str(robvel)])
          detection_meas =[];
             
 end
 