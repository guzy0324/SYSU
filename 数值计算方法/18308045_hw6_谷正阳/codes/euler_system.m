function [x, y] = euler_system(f, g, t, x, y, h, M)
    for i = 1:M
        x0 = x;
        y0 = y;
        x = x + h * f(t, x0, y0)
        y = y + h * g(t, x0, y0)
        t = t + h;
    end
end