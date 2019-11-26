function  [sep, sem] = new_kalman_sim_test(sem, sensor_data, A, C, Q, R, P0)
          if sensor_data(1) >= 0.5
            Q = [(0.035 * sensor_data(1))^2, 0;
                    0,  (0.035 * sensor_data(1))^2];
          end
          if sensor_data(1) >= 0.5
                R = [(0.05*sensor_data(1))^2];
          end
          if sensor_data(1) >= 0.5
                P0 = [(0.035 * sensor_data(1))^2, 0;
                        0 , (0.035 * sensor_data(1))^2];
          end
    Pm = P0;
    [K] = sim_vel_est_kalman_filt_1D( A, C, Q, R, Pm);
    sep = sem + K*(sensor_data(1) - C*sem);
    pose = [sep(1)];
    velex = [sep(2)];
          % prediction step
    sem = A*sep; %+ B*vele; % pass this final value

