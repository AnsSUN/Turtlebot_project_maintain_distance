
clear all, close all, clc

load AcfMyModelDetector.mat %generated on 02-16-2018
% training the acf detector to get the turtlebot detection
% foregroundDetector = vehicleDetectorACF('full-view');

% foregroundDetector = vision.PeopleDetector('ClassificationThreshold', ... 
%          0, 'MergeDetections', false);

      
I = imread('trafficjamcars-580x358.jpg'); 
% [bbox,score] = acfDetect(I); % reference before used.
bbs = acfDetect(I, detector); % need improvement.

I1 = insertObjectAnnotation(I,'rectangle',bbs(:,1:4),cellstr(num2str(bbs(:,5))),'Color','r');
  
[selectedBbox,selectedScore] = selectStrongestBbox(bbs(:,1:4),bbs(:,5), 'OverlapThreshold', 0.001, 'RatioType', 'Union'); 
I2 = insertObjectAnnotation(I,'rectangle',selectedBbox,cellstr(num2str(selectedScore)),'Color','r');
    
figure, imshow(I1); 
title('Detected cars and detection scores before suppression'); 

figure, imshow(I2); 
title('Detected cars and detection scores after suppression');

