%abc1.m
temp = [2.71828182; 98.350; 0.000068];
temp_a = [2.7182; 98.000; 0.00006];
E = abs(temp - temp_a);
R = E ./ abs(temp);
Ex = E(1);
Rx = R(1);
Ey = E(2);
Ry = R(2);
Ez = E(3);
Rz = R(3);