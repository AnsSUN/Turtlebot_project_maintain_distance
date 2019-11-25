function x_y_coord = lds_convert(detect_rad)  %#codegen
% This function converts the Lidar detections into [x, y] coordinates.
% at different degrees of the detections.

% flipping the array values to make values in the form (60: 1 : 360 : 301) degree values.
% i.e. [60: 0: -59] degrees.
%theta = [flip(linspace(1, length(detect_rad(1:60)), length(detect_rad(1:60)))), -linspace(0, length(detect_rad(61:120))-1, length(detect_rad(61:120)))];
theta = [flip(linspace(1, length(detect_rad(1:15)), length(detect_rad(1:15)))), -linspace(0, length(detect_rad(16:30))-1, length(detect_rad(16:30)))];
theta = deg2rad(theta);
x_y_coord = zeros(length(detect_rad), 2);
x= detect_rad.*cos(theta');
y= detect_rad.*sin(theta');
x_y_coord(:, 1) = x;
x_y_coord(:, 2) = y;
%x_y_coord(:, 3) = 0.18; %the height of the Lidar placed on the turtlebot.
end