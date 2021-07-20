%a1.m
X = [-2; -1; 0; 1; 2];
Y = [1; 2; 3; 3; 4];
F = [1.2; 1.9; 2.6; 3.3; 4.0];
sum_X_2 = sum(X.^2)
sum_X = sum(X)
sum_XY = sum(X .* Y)
N = size(X, 1)
sum_Y = sum(Y)
E2 = sqrt(1 / N * sum((F - Y).^2))