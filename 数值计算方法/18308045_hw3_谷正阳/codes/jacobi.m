%jacobi.m
function [P] = jacobi(A, B, P0, k)
    P = zeros(size(A, 2), k);
    coef = [-A, B];
    for i = 1:size(A, 1)
        coef(i, :) = coef(i, :) / A(i, i);
        coef(i, i) = 0;
    end
    P(:, 1) =  coef * [P0; 1];
    for i = 2:k
        P(:, i) = coef * [P(:, i - 1); 1];
    end
end