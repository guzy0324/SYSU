%gauss_seidel.m
function [P] = gauss_seidel(A, B, P0, k)
    P = zeros(size(A, 2), k);
    coef = [-A, B];
    coef = coef ./ diag(A);
    coef(1:size(coef, 2):end) = 0;
    P(:, 1) = P0;
    for j = 1:size(A, 2)
        P(j, 1) = coef(j, :) * [P(:, 1); 1];
    end
    for i = 2:k
        P(:, i) = P(:, i - 1);
        for j = 1:size(A, 2)
            P(j, i) = coef(j, :) * [P(:, i); 1];
        end
    end
end