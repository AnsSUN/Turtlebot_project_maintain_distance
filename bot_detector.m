detector = peopleDetectorACF;
I = imread('visionteam1.jpg');
[bboxes,scores] = detect(detector,I);


I = insertObjectAnnotation(I,'rectangle',bboxes,scores);
figure
imshow(I)
title('Detected People and Detection Scores')