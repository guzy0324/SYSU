function [y2] = RK41step(f, t1, y1, h)
    k1 = f(t1, y1)
    k2 = f(t1 + 0.5 * h, y1 + 0.5 * k1 * h)
    k3 = f(t1 + 0.5 * h, y1 + 0.5 * k2 * h)
    k4 = f(t1 + h, y1 + k3 * h)
    y2 = y1 + (k1 + 2 * k2 + 2 * k3 + k4) * h / 6
end