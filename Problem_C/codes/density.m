function [d] = density(theta, n, X)
    A = [ones(size(X, 1), 1), X, X .^ 2, X .^ 3, X .^4, X .^5]; 
    temp = 1:n - 1;
    d = A(:, 1:n - 1) * (theta(2:n, 1) .* temp');
end