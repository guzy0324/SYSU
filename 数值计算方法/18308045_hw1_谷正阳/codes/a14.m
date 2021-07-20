%a14.m
a = [-12; -1; -13; 1; 1];
c = 3;
[P] = Horner(a, c);
P_ver = [1, c, c^2, c^3, c^4] * a;
