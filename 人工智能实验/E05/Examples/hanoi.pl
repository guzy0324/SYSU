hanoi(N):-move(N,a,b,c).
move(1,A,_,C):-inform(A,C).
move(N,A,B,C):-N1 is N-1,move(N1,A,C,B),inform(A,C),move(N1,B,A,C).
inform(Loc1,Loc2):-nl,write('from '),write(Loc1),write(' to '),write(Loc2).
