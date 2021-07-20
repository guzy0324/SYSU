%p137.m
AB1 = [2, 4, -6, -4;
    1, 5, 3, 10;
    1, 3, 2, 5];
UV1 = eliminate(AB1);
solution1 = solve(UV1);

AB9 = [2, 4, -4, 0, 12;
    1, 5, -5, -3, 18;
    2, 3, 1, 3, 8;
    1, 4, -2, 2, 8];
UV9 = eliminate(AB9);
solution9 = solve(UV9);