% ex2.m
m = 100;
close();
for N = 4:6
    figure();
    X = (1:N + 1)';
    Y = cos(X);
    P = zeros(1, m);
    for i = 1:m
        P(1, i) = lagrange(i + N, X, Y);
    end
    y = cos(1 + N:m + N);
    E = y - P;
    plot(1 + N:m + N, abs(E).^(1 / (N + 1)), '.');
    tit = sprintf('N=%d', N);
    yla = sprintf('(E_%d(x))^{1/%d}', N, N + 1);
    title(tit);
    xlabel('x');
    ylabel(yla);
end
