%definite_integral.m
function [i] = definite_integral(a, c1, c2)
    ai = [a ./ (size(a, 1):-1:1)'; 1];
    i = Horner(ai, c2) - Horner(ai, c1);
end