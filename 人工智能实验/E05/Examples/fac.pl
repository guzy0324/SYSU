fib(1,1).
fib(2,1).
fib(N,Ret) :- N > 2, N1 is N -1, N2 is N -2, fib(N1,Prv1), fib(N2,Prv2), Ret is Prv2 + Prv1.

factorial(0,1).
factorial(1,1).
factorial(N,Ret) :-  N > 1, N1 is N - 1, factorial(N1, Ret1), Ret is N * Ret1.