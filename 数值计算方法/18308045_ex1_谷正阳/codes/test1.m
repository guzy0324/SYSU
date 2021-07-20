sz = 1000;
km = 1000;
gap = 100;
A = rand(sz);
B = rand(sz, 1);
P0 = zeros(sz, 1);
k = gap:gap:km;
t1 = zeros(size(k));
t2 = zeros(size(k));
for i = 1:size(k, 2)
    tic
    gauss_seidel(A, B, P0, k(i));
    t1(i) = toc;
end
for i = 1:size(k, 2)
    tic
    gauss_seidel_parallel(A, B, P0, k(i));
    t2(i) = toc;
end
kk = gap:km;
tt1 = spline(k, t1, kk);
tt2 = spline(k, t2, kk);
figure
hold on
plot(kk, tt1)
plot(kk, tt2)
legend('Gauss-Seidel','Gauss-Seidel Parallel');
clear