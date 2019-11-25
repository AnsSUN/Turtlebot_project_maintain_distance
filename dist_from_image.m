load('turtlebot_img_detect_data.mat');
load('turtlebot_cameracalibration.mat');
%d = (.2*.500603560675451)/bboxes(:, 3);

d= (499*200*640)/(bboxes(:, 3)*125);