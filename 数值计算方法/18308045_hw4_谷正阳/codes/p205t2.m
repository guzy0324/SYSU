%p205t2.m
a = [-0.04; 0.14; -0.16; 2.08];
P3 = Horner(a, 3);
Pd3 = derivative(a, 3);
Pt3 = definite_integral(a, 0, 3);
P45 = Horner(a, 4.5);
x = [0; 1; 2; 4];
y = [2.08; 2.02; 2.00; 1.12];
AB = [x.^0, x.^1, x.^2, x.^3, y];
coe = solve(eliminate(AB));