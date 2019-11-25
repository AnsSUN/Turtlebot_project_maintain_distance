%start rosinit and then bringup the sensors of the turtlebot before running
%this code
%bboxes=[x y width height]. This vector specifies the upper left corner and size of that corresponding bounding box in pixels.
%clear all, close all, clc
%draw_line = line([0, 640],[240, 240]);
t = rostime('now');
if(ismember('/raspicam_node/image/compressed', rostopic('list')))
    imsub = rossubscriber('/raspicam_node/image/compressed');
    flag =1;
    load('use_for_turtlebot_detection.mat');
    while(flag)
        img = receive(imsub);
        img.Format = 'bgr8; jpeg compressed bgr8';
        I = readImage(img);
        bboxes = detect(acfDetector, readImage(img));
        %bboxes1 = [65, 320, 130, 110];
        bboxes2 = [290, 210, 90, 75];
        if ~isempty(bboxes)
            x_rel_dist = plot_pix_vs_dist(bboxes(3));
            pixels = bboxes2(1)+bboxes2(3) - 205;
            f= (pixels*9)/4;
            y = (pixels*x_rel_dist)/f;
        end
        I = insertObjectAnnotation(I,'rectangle',bboxes, 'Turtlebot');
        %I = insertObjectAnnotation(I,'rectangle',bboxes1, 'reference');
        I = insertObjectAnnotation(I,'rectangle',bboxes2, 'reference');
        save('turtlebot_img_detect_data.mat','bboxes')
        imshow(I); 
        line([0, 410],[154, 154]);
        line([205, 205], [0, 308]);  
    end
else
    print("Camera video is not publishing rostopic: /raspicam_node/image/compressed.");
end
%save('turtlebot_img_detect_data.mat','bboxes')
clear