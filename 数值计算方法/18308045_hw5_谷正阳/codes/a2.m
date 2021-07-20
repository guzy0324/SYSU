%a2.m
X = [-2; -1; 0; 1; 2];
Y = [-5.8; 1.1; 3.8; 3.3; -1.5];
sum_X_4 = sum(X.^4)
sum_X_3 = sum(X.^3)
sum_X_2 = sum(X.^2)
sum_Y_X_2 = sum(Y .* X.^2)
sum_X = sum(X)
sum_Y_X = sum(Y .* X)
N = size(X, 1)
sum_Y = sum(Y)
solve([sum_X_4, sum_X_3, sum_X_2, sum_Y_X_2;
    sum_X_3, sum_X_2, sum_X, sum_Y_X;
    sum_X_2, sum_X, N, sum_Y])