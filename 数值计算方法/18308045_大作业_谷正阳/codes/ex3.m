% ex1.m
for i = 1:3
    N = unidrnd(10);
    dif = @(x)(-1)^N * factorial(N) / x^(N + 1);
    X = 5 + 10 .* rand(N + 1, 1);
    YY = log(X);
    e = -0.001 + 0.002 .* rand(N + 1, 1);
    Y = (1 + e) .* YY;
    x = 15 + 10 .* rand(1, 1);
    y = log(x)
    P = lagrange(x, X, Y);
    E1 = prod(x - X) * dif(min(min(X), x)) / factorial(N + 1);
    E2 = prod(x - X) * dif(max(max(X), x)) / factorial(N + 1);
    if E1 > E2
        E1 = E1 + E2;
        E2 = E1 - E2;
        E1 = E1 - E2;
    end
    P_plus_E1 = P + E1
    P_plus_E2 = P + E2
    E11 = E1;
    E22 = E2;
    for i = 1:length(X)
        XX = [X(1:i - 1); X(i + 1:length(X))];
        if Y(i) * prod(x - XX) ./ prod(X(i) - XX) > 0
            E11 = E11 + (1 / 1.001 - 1) * Y(i) * prod(x - XX) ./ prod(X(i) - XX);
            E22 = E22 + (1 / 0.999 - 1) * Y(i) * prod(x - XX) ./ prod(X(i) - XX);
        else
            E11 = E11 + (1 / 0.999 - 1) * Y(i) * prod(x - XX) ./ prod(X(i) - XX);
            E22 = E22 + (1 / 1.001 - 1) * Y(i) * prod(x - XX) ./ prod(X(i) - XX);
        end
    end
    P_plus_E11 = P + E11
    P_plus_E22 = P + E22
end