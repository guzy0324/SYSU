fib(1,1).
fib(2,1).
fib(N,Ret) :- N > 2, N1 is N -1, N2 is N -2, fib(N1,Prv1), fib(N2,Prv2), Ret is Prv2 + Prv1.
