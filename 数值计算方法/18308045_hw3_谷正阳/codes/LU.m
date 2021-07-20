%LU.m
function [L, U] = LU(A)
    U = A;
    L = eye(size(U));
    for i = 2:size(A, 1)
        for j = 1:(i - 1)
            UT = U(i, j) / U(j, j);
            U(i, :) = U(i, :) - UT * U(j, :);
            L(i, j) = L(i, j) + UT * L(j, j);
        end
    end
end