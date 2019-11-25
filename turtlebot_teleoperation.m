
handles.odomSub = rossubscriber('/odom', 'BufferSize', 25);
receive(handles.odomSub,3);
handles.laserSub = rossubscriber('/scan', 'BufferSize', 5);
receive(handles.laserSub,3);

handles.velPub = rospublisher('/cmd_vel');

