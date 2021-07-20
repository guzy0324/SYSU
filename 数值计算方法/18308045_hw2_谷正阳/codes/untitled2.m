a = 1;
b = 7;
for i = 1:100
    c = (a + b) / 2
    if (g(c) > 0 && g(a) < 0) || (g(c) < 0 && g(a) > 0)
        b = c;
    elseif (g(c) > 0 && g(b) < 0) || (g(c) < 0 && g(b) > 0)
        a = c;
    elseif (g(c) == 0)
        break;
    else
        break;
    end
end