function lds_detect_velo = lds_vel_cal(lds_coord_init) %#codegen
% this function calculates the velocity of detected objects 
% it will return value zero while assigning the persistant values
% therefore make a condition in your program to not to use it while
% it is spiting out  [0, 0].

persistent prev_time
persistent prev_coord 
currTime = datetime;

if isempty(prev_time)
    if isempty(prev_coord)
        prev_time = currTime;
        prev_coord = lds_coord_init;
    end
end

dt= seconds(currTime - prev_time);
dpos = lds_coord_init - prev_coord;
%disp(['diff time' num2str(dt)]);
%disp(['diff position' num2str(dpos)]);
if dt==0
    lds_detect_velo = [0, 0]; % because of comparing afterwards.
else
    lds_detect_velo = dpos ./ dt;
end
%disp(['Velocity' num2str(lds_detect_velo)]);


end
