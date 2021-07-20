%factorize.m
function [L, U] = factorize(A)
    U = A;
    for i = 2:size(A, 1)
        for j = 1:(i - 1)
            U(i, :) = U(i, :) - U(i, j) / U(j, j) * U(j, :);
        end
    end
    L = A / U;
end