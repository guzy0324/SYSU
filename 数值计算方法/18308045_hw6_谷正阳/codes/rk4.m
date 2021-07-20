function R = rk4(f, a, b, ya, M)
    %Input - f is the function entered as a string ’f’
    %- a and b are the left and right endpoints
    %- ya is the initial condition y(a)
    %- M is the number of steps
    %Output - R=[T’ Y’] where T is the vector of abscissas
    %and Y is the vector of ordinates
    h = (b - a) / M;
    T = zeros(1, M + 1);
    Y = zeros(1, M + 1);
    T = a:h:b;
    Y(1) = ya;
    for j = 1:M
        k1 = h * feval(f, T(j), Y(j));
        k2 = h * feval(f, T(j) + h / 2, Y(j) + k1 / 2);
        k3 = h * feval(f, T(j) + h / 2, Y(j) + k2 / 2);
        k4 = h * feval(f, T(j) + h, Y(j) + k3);
        Y(j + 1) = Y(j) + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    end
    R = [T' Y'];
end
