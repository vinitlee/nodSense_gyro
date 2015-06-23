% --> data

% C1 =[[0.7923    0.5298    0.3025]
%     [-0.5298    0.8434   -0.0894]
%     [-0.3025   -0.0894    0.9489]];

% C2 = [[0.5018    0.8555   -0.1276]
%       [-0.8555   0.5127    0.0727]
%       [0.1276    0.0727    0.9892]];

C1 = Ai;
C2 = Bi;

wdata = data(:,:);
% wdata(:,4) = wdata(:,4) + 0.4*wdata(:,4+2);
% wdata(:,10) = wdata(:,10) - 0.4*wdata(:,10+2);
for n = 1:length(wdata)
    wdata(n,1:3) = (C1*data(n,1:3)')';
    wdata(n,4:6) = (C1*data(n,4:6)')';
    wdata(n,7:9) = (C2*data(n,7:9)')';
    wdata(n,10:12) = (C2*data(n,10:12)')';
end

for n = [1,4]
    figure(n)
%     t = 0:0.052:0.052*(length(wdata)-1);
    t = 1:(length(wdata));
    for a = [1,2,3]
        subplot(3,1,a);
        plot(t,wdata(:,n+a-1),t,wdata(:,n+6+a-1));
    end
end