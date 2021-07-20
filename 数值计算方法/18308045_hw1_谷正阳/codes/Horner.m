%Horner.m
function [P] = Horner(a, c)
    b = zeros(size(a));
    b(size(a)) = a(size(a));

    for i = size(a, 1) - 1:-1:1
        b(i) = b(i + 1) * c + a(i);
    end

    P = b(1);
end
