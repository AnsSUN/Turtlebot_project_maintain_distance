function vision_measurements = image_toworld_coord_test(x_lds_meas)
%use 23rd  no. rotation matrix to get the world coordinates which is:.
%[x,
% -y] 
% the actual world coordinates are: 
%[y,
% z]
%Therefore, the mapping of matlab output to the actual world is:
%[y, = [x,
%z]     -y]
% Similarly, for translation vectors: no. third is taken.
% Image points, specified as an M-by-2 matrix containing M [x, y] coordinates of image points.
%  M [x, y] coordinates of image points. M represents the number of undistorted points in [x, y] world coordinates.
% bboxes=[x y width height]. This vector specifies the upper left corner and size of that corresponding bounding box in pixels.
% calculating the the velocity from the vision system by implementing the constant
% velocity calman filter which normaly starts with the sensor reading of [x, y, z]
% It also has scaling factor from the camera parameter and world z
% coordinates for velocity calculation.

load('turtlebot_cameracalibration.mat');
load('turtlebot_img_detect_data.mat'); % bboxes info inside this file
rot_mat = [        0.9991,   -0.0061,    0.0423;
    0.0040,    0.9987,    0.0507;
   -0.0425,   -0.0505,    0.9978];
% try to get last value i.e. x coordinate of the real world through
% different sensor or do some estimation calculations to get it.
% this translational matrix is made from x value as 365.952159941607 to get
% accurate answer.
trans_vect = [14.6270152877568,-42.7098397511075, x_lds_meas]; % x_lds_meas taken from lds to make the transition vector.

% you can take the last value of trans_vect directly for calculating x coordinate.  
img_points = [bboxes(:, 1), bboxes(:, 2); % upper left: [x, y]
              bboxes(:, 1)+ bboxes(:, 3), bboxes(:, 2); % upper right: [x + width, y]
              bboxes(:, 1),  bboxes(:, 2)+ bboxes(:, 4); % bottom left: [x, y+height]
              bboxes(:, 1)+ bboxes(:, 3), bboxes(:, 2)+ bboxes(:, 4); % bottom right: [x+width, y+height]
              bboxes(:, 1) + bboxes(:, 3)/2, bboxes(:, 2)+ bboxes(:, 4)/2]; % Centroid: [x+ width/2, y+height/2]

worldPoints = pointsToWorld(cameraParams, rot_mat, trans_vect, img_points);
% So the points are converted to world coordinates!!! 
converttoact = [worldPoints(:, 1), -worldPoints(:, 2)]; % change according to rotation matrix and trans vect.

% getting almost accurate height and width!!!
% all diamensions in mm, therefore converting to meters.

height = -(converttoact(3, 2) - converttoact(1, 2))/1000; 
width = (converttoact(2, 1)-converttoact(1, 1))/1000;
% take this value for accurate centroid location in the world. coordinates
% in meters!! i.e. [x, y, z] relative to turtlebot1. 
% return this value for sensor fusion if you can estimate velocity vx, vy.
% In future avoid z coordinate or delete it as it will not impact in sensor
% fusion algorithms.
centinworld = [ trans_vect(1, 3)/1000; converttoact(1, 1)/1000 + width/2; converttoact(1, 2)/1000 + height/2];

% taking height in the images and calculating the ratio for the kalman
% filter. let take height of the turtlebot in real world is  20cm

height_actual = 200; % in mm.
scalefact = height_actual/bboxes(:, 4);
detected = objectDetection(0, centinworld, 'MeasurementNoise',scalefact*eye(3));
filter = initcvekf(detected); % constant vel. applied
[xpred, Ppred] = predict(filter);
[xcorr, Pcorr] = correct(filter, centinworld);
[xpred, Ppred] = predict(filter);

%Trying scaling of object to predict longitudnal velocity
% there is no need of z world coordinate as no upward and downward motion
persistent  height_img;
persistent prev_time;
persistent y_coord;
currTime = datetime;
if isempty(prev_time)
    if isempty(height_img)
        prev_time = currTime;
        height_img = bboxes(:, 4);
        y_coord = centinworld(2, :);
    end
end
% Change in height  in 1 second is more convinient to calculate the
% velocity. 
dt= seconds(currTime - prev_time);
d_height = bboxes(:, 4) - height_img; % in the image not in world check it
y_coord_meas = centinworld(2, :); % this is in the world.
d_y_coord = y_coord_meas - y_coord;
if dt==0
    heightimg_velo = 0; % because of comparing afterwards.
    y_coord_meas = 0;
else
    heightimg_velo = d_height/ dt;
    y_coord_meas = d_y_coord/dt;
end

% creating th measurement matrix: [x, y, vx, vy]
vision_measurements = [centinworld(1, :), centinworld(2, :), heightimg_velo, y_coord_meas];
end

% for i = 1:10
%   vision_measurements = image_toworld_coord_test(365.952159941607);
% 
%      if any(vision_measurements ~= 0) % condition when velocity of object is not zero
%           Measurement = vision_measurements;
%           clear image_toworld_coord_test;
%      end
%  end
