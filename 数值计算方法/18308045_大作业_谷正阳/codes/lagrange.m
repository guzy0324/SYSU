function [P] = lagrange(x, X, Y)
% X表示已知的N+1个点横坐标，是N+1维的列向量
% Y表示已知的N+1个点纵坐标，是N+1维的列向量
% x表示要估计点的横坐标
% P表示要估计点的纵坐标估计值
    P = 0;

    for i = 1:length(X)
        XX = [X(1:i - 1); X(i + 1:length(X))];
        P = P + Y(i) * prod(x - XX) ./ prod(X(i) - XX);
    end

end
