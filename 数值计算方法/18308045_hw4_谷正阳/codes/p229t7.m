%p229t7
xk = [0; 1; 2; 3; 4];
f = [0; 0.75; 2.25; 3; 2.25];
t = divided_difference_table(f);
real_t = [xk, t];

x = 1.5;
P1 = zeros(size(f, 1) - 1, 1);
tt = t(1:size(t, 1) + 1:size(t, 1) * size(t, 1));
tt(1, 2:size(tt, 2)) = tt(1, 2:size(tt, 2)) * (x - xk(1, 1));
P1(1) = t(1, 1) + tt(1, 2);
for i = 2:size(f, 1) - 1
    tt(1, i + 1:size(tt, 2)) = tt(1, i + 1:size(tt, 2)) * (x - xk(i, 1));
    P1(i) = P1(i - 1) + tt(1, i + 1);
end
y1 = 3 * (sin(pi * x / 6)) ^ 2;
d1 = abs(P1 - y1);

x = 3.5;
P2 = zeros(size(f, 1) - 1, 1);
tt = t(1:size(t, 1) + 1:size(t, 1) * size(t, 1));
tt(1, 2:size(tt, 2)) = tt(1, 2:size(tt, 2)) * (x - xk(1, 1));
P2(1) = t(1, 1) + tt(1, 2);
for i = 2:size(f, 1) - 1
    tt(1, i + 1:size(tt, 2)) = tt(1, i + 1:size(tt, 2)) * (x - xk(i, 1));
    P2(i) = P2(i - 1) + tt(1, i + 1);
end
y2 = 3 * (sin(pi * x / 6)) ^ 2;
d2 = abs(P2 - y2);
