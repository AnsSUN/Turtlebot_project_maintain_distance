%{
x_vis_est = [0.299175381;
0.431957964;
0.504308888;
0.504308888;
0.836328657;
0.931061201;
1.003062847;
1.003062847;
1.09991917;
1.201003318;
1.201003318;
1.493289662;
1.624259247];
%}
x_vis_est = [0.309626268;
0.408367912;
0.506601746;
0.602841822;
0.631934749;
0.82677332;
0.82677332;
0.989604492;
1.185392122;
1.366686639;
1.615033106;
1.615033106;
1.777267847];

x_act = [0.3;
0.4;
0.5;
0.6;
0.7;
0.8;
0.9;
1;
1.2;
1.3;
1.4;
1.5;
1.6];

x_lds_est = [0.31386533;
0.4046438;
0.51245773;
0.57633847;
0.64796746;
0.76893926;
0.86529797;
0.96911395;
1.1811413;
1.2822309;
1.3819406;
1.5041336;
1.6015576];

delta = x_vis_est - x_lds_est;

figure()
ax(1) = subplot(2,1,1);

scatter(x_act, x_lds_est,'filled')
hold on
scatter(x_act, x_vis_est,'filled')
hold off
title('comparison between LDS and vision measurement ')
xlabel('actual distance (m)')
ylabel('estimated distance (m)')
legend('lidar measurement','vision measurement')
grid on
ax(2) = subplot(2,1,2);
bar(x_act, delta)
xlabel('actual distance (m)')
ylabel('estimated distance (m)')
legend('residual error')
grid on
linkaxes(ax,'x')
