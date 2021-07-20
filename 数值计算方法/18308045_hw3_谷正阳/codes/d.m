%d.m
function [res] = d(A)
    res = zeros(1, size(A, 2) - 1);
    for i = 1:size(A, 2) - 1
        res(1, i) = sum(abs(A(:, i + 1) - A(:, i)));
    end
end