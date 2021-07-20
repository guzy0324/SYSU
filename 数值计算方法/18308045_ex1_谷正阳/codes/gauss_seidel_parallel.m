%gauss_seidel_parallel.m
function [P] = gauss_seidel_parallel(A, B, P0, k)
    P = zeros(size(A, 2), k);
    coef = [-A, B];
    coef = coef ./ diag(A);
    coef_ex = triu(coef, 1);
    for i = 2:size(A, 1)
        for j = 1:i - 1
            coef_ex(i, :) = coef_ex(i, :) + coef(i, j) * coef_ex(j, :);
        end
    end
    P(:, 1) =  coef_ex * [P0; 1];
    for i = 2:k
        P(:, i) = coef_ex * [P(:, i - 1); 1];
    end
end