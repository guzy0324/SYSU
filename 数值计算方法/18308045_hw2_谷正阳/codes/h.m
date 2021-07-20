function [y] = h(x)
    y = x - (x ^ 3 - 3 * x - 2) / (3 * x ^ 2 - 3);
end
