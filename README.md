# Turtlebot_project_maintain_distance
 This project have experimental validation of different control strategies for mobile robots.

Hardware and Software Setup:
--------------

1.) The turtlebot setup can be found in this link: http://emanual.robotis.com/docs/en/platform/turtlebot3/getting_started/#getting-started. This e-manual provides an overall setup of hardware and software.

2.) This project was written in Matlab. Therefore, the ROS-Matlab interface needs to be set up which is provided in this link: https://www.mathworks.com/help/ros/ug/get-started-with-ros.html. For connection to the ROS-Matlab network is provided in this https://www.mathworks.com/help/ros/ug/connect-to-a-ros-network.html. Try to exchange data between robots and the Matlab platform. And this information is provided in this tutorial: https://www.mathworks.com/help/ros/ug/exchange-data-with-ros-publishers-and-subscribers.html.

3.) Moreover, this system uses the raspberry pi camera and LDS sensors for object detection. So, the raspberry pi camera v2 should be installed and tested by transmitting the data to the master PC. After this setup, calibrate the camera by default calibration file which is provided by robotis in the raspberry pi ROS package.

4). First Train the 'acfdetector' from the image datasets of the turtlebot which can be found here: https://drive.google.com/drive/u/2/folders/1JvySZrE_nyIaQkdfPsGJY9gh3zDL_Z1q. You can use any type of detector you want to train and get the bounding boxes in the images.

5.) After training and generating the bounding box, please make sure the image size transmission is 410X308 pixels. This can be changed in the roslaunch file provided in the ROS camera package.  

Application of turtlebots
--------------

1.) After finishing up all the above steps, initialize the ROS environment by 'rosinit' command in the Matlab command window. This will initialize the Master PC to exchange the data between the robot and the PC. After this, run the main file: 'acc_turtle_operate_test.m'.

2.) Change the functions to run different controllers to maintain a safe distance. This system works only on Longitudinal autonomy. If possible try to restrict the motion of turtlebots in a straight line.
