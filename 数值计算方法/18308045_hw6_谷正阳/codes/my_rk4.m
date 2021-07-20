function [y] = my_rk4(f, t, y, h, M)
    for i = 1:M
        y = RK41step(f, t, y, h);
        t = t + h;
    end
end