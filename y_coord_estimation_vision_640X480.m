% calculating the y coordinate from the image
% line([320, 320], [0, 480]) %vertical line on image for reference.

%  bboxes1 = [65, 320, 130, 110];
%  bboxes2 = [475, 330, 130, 110];
% pix_fromx : x pixel centroid point from image (0,0) i.e. x + (width/2)
function y_vis = y_coord_estimation_vision_640X480(pix_fromx, x_rel_dist_vis)
   bboxes2 = [475, 330, 130, 110]; % this is the reference bounding box for calculation.
   pixels = bboxes2(1)+bboxes2(3) - 320; % change 320 i.e. 1/2*(size of image in x direction) value according to pixel size of the image
   f= (pixels*9)/4; % constant
   new_pixel_value = pix_fromx - 320; % change 320 i.e. 1/2*(size of image in x direction) value according to pixel size of the image
   %pixel value change according to position.
   y_vis = (new_pixel_value * x_rel_dist_vis)/640;
end