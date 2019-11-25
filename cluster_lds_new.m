%load('turtlebot_lds_detect_data.mat');
% num_point = size(Measurement_lds);
% for det = 1: num_point(1, 1)
%     sensors{det, 1} = struct('SensorIndex', 1, 'Measurement', Measurement_lds(det, :)', 'ObjectClassID', 1);
% end
% 
% 
% detections = [sensors{:, 1}];
% vehicleLength = 0.20;
% detectionClusters = cluster_check_lds(detections, vehicleLength);

function detectionClusters = cluster_lds_new(detections, vehicleSize) %#codegen
N = numel(detections);
distances = zeros(N);
for i = 1:(N)
    for j = i+1:N
        if detections(1, i).SensorIndex == detections(1, j).SensorIndex
            distances(i,j) = norm(detections(1, i).Measurement(1:2) - detections(1, j).Measurement(1:2));
        else
            distances(i,j) = inf;
        end
    end
end
leftToCheck = 1:N;
i = 0;
detectionClusters = cell(N,1);
% if array is empty!!
if (distances)==0
    detectionClusters{1} = detections(1,1);
    detectionClusters{1}.Measurement = [0; 0];
    detectionClusters(2:end) = [];
else
    while ~isempty(leftToCheck)    
        % Remove the detections that are in the same cluster as the one under
        % consideration
        underConsideration = leftToCheck(1);
        clusterInds = ( distances(underConsideration, leftToCheck) < vehicleSize);
        detInds = leftToCheck(clusterInds);
        clusterDets = [detections(1, detInds)];
        for k = numel(clusterDets)
            
        clusterMeas = [clusterDets(1).Measurement];
        meas = mean(clusterMeas, 2);
        %disp(['##1 -- cluster meas :',(meas)])
        meas2D = [meas(1:2)];
        i = i + 1;
        detectionClusters{i} = detections(1, detInds(1));
        detectionClusters{i}.Measurement = meas2D;
        leftToCheck(clusterInds) = [];    
    end
    detectionClusters(i+1:end) = [];


end
end
