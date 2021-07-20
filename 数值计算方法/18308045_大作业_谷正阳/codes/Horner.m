function [P] = Horner(a, c)
% a是系数向量，从次数小到次数大排列，列向量
% c是一组函数自变量，列向量
% P是一组估计值，列向量
    c = c';
    b = zeros(length(a), length(c));
    b(length(a), :) = a(length(a));

    for i = length(a) - 1:-1:1
        b(i, :) = b(i + 1, :) .* c + a(i);
    end

    P = b(1, :)';
end
