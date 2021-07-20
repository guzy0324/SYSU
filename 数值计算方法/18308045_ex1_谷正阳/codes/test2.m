szm = 1500;
gap = 150;
k = 500;
A = rand(szm);
B = rand(szm, 1);
P0 = zeros(szm, 1);
sz = gap:gap:szm;
t1 = zeros(size(sz));
t2 = zeros(size(sz));
for i = 1:size(sz, 2)
    tic
    gauss_seidel(A(1:sz(i), 1:sz(i)), B(1:sz(i), 1), P0(1:sz(i), 1), k);
    t1(i) = toc;
end
for i = 1:size(sz, 2)
    tic
    gauss_seidel_parallel(A(1:sz(i), 1:sz(i)), B(1:sz(i), 1), P0(1:sz(i), 1), k);
    t2(i) = toc;
end
ssz = gap:szm;
tt1 = spline(sz, t1, ssz);
tt2 = spline(sz, t2, ssz);
figure
hold on
plot(ssz, tt1)
plot(ssz, tt2)
legend('Gauss-Seidel','Gauss-Seidel Parallel');
clear