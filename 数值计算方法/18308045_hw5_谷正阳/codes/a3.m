x = [1; 2; 3; 4; 5];
y = [0.6; 1.9; 4.3; 7.6; 12.6];
X = x;
Y = log(y);
sum_X_2 = sum(X.^2);
sum_X = sum(X);
sum_XY = sum(X .* Y);
N = size(X, 1);
sum_Y = sum(Y);
solve([sum_X_2, sum_X, sum_XY;
    sum_X, N, sum_Y]);
A = ans(1, 1)
B = ans(2, 1)
C = exp(B)
