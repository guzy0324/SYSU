% ex1.m
for i = 1:5
    N = unidrnd(10);
    coef = randn(N + 2, 1);
    dif = coef(length(coef)) * factorial(N + 1);
    X = randn(N + 1, 1);
    Y = Horner(coef, X);
    x = randn(1, 1);
    y = Horner(coef, x)
    P = lagrange(x, X, Y)
    E = prod(x - X) * dif / factorial(N + 1)
end
