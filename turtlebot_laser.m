%start rosinit and then bringup the sensors of the turtlebot before running
%this code

laser = rossubscriber('/scan');

tic;
while toc < 10
  scan = receive(laser,3);
  plot(scan);
end