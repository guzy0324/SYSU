%derivative.m
function [d] = derivative(a, c)
    ad = a(1:size(a, 1) - 1) .* (size(a, 1) - 1:-1:1);
    d = Horner(ad, c);
end