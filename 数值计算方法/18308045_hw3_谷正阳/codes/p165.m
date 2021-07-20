%p165.m
A1 = [4, -1;
    1, 5];
B1 = [15; 9];
P11 = jacobi(A1, B1, zeros(size(A1, 2), 1), 3);
P12 = gauss_seidel(A1, B1, zeros(size(A1, 2), 1), 3);
P13 = gauss_seidel_parallel(A1, B1, zeros(size(A1, 2), 1), 3);
d11 = d(P11);
d12 = d(P12);

A3 = [-1, 3;
    6, -2];
B3 = [1; 2];
P31 = jacobi(A3, B3, zeros(size(A3, 2), 1), 3);
P32 = gauss_seidel(A3, B3, zeros(size(A3, 2), 1), 3);
P33 = gauss_seidel_parallel(A3, B3, zeros(size(A3, 2), 1), 3);
d31 = d(P31);
d32 = d(P32);

A5 = [5, -1, 1;
    2, 8, -1;
    -1, 1, 4];
B5 = [10; 11; 3];
P51 = jacobi(A5, B5, zeros(size(A5, 2), 1), 3);
P52 = gauss_seidel(A5, B5, zeros(size(A5, 2), 1), 3);
P53 = gauss_seidel_parallel(A5, B5, zeros(size(A5, 2), 1), 3);
d51 = d(P51);
d52 = d(P52);