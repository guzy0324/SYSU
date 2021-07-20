function [x, y] = rk4_system(f, g, t, x, y, h, M)
    for i = 1:M
        x1 = x;
        y1 = y;
        f1 = f(t, x1, y1)
        g1 = g(t, x1, y1)
        f2 = f(t + 0.5 * h, x1 + 0.5 * f1 * h, y1 + 0.5 * g1 * h)
        g2 = g(t + 0.5 * h, x1 + 0.5 * f1 * h, y1 + 0.5 * g1 * h)
        f3 = f(t + 0.5 * h, x1 + 0.5 * f2 * h, y1 + 0.5 * g2 * h)
        g3 = g(t + 0.5 * h, x1 + 0.5 * f2 * h, y1 + 0.5 * g2 * h)
        f4 = f(t + h, x1 + f3 * h, y1 + g3 * h)
        g4 = g(t + h, x1 + f3 * h, y1 + g3 * h)
        x = x1 + (f1 + 2 * f2 + 2 * f3 + f4) * h / 6
        y = y1 + (g1 + 2 * g2 + 2 * g3 + g4) * h / 6
        t = t + h;
    end
end