a = -2.4;
b = -1.6;
for i = 1:4
    c = b - f(b) * (b - a) / (f(b) - f(a))
    if (f(c) > 0 && f(a) < 0) || (f(c) < 0 && f(a) > 0)
        b = c;
    elseif (f(c) > 0 && f(b) < 0) || (f(c) < 0 && f(b) > 0)
        a = c;
    elseif (f(c) == 0)
        break;
    end
end