%ab3.m
p1 = [1.414; 31.415];
p2 = [0.09125; 0.027182];
d = [4; 5];
Sum = p1 + p2;
product = p1 .* p2;
sum_d = Sum .* 10.^(1 - d) ./ 2;
product_d = product .* 10.^(1 - d) ./ 2;
sum_ran = [Sum - sum_d, Sum + sum_d];
product_ran = [product - product_d, product + product_d];