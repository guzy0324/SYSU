a(tony).
a(mike).
a(john).
l(tony,rain).
l(tony,snow).

c(X) :- a(X),ns(X).
nc(X) :- \+ c(X).
nc(Y) :- l(Y,rain).
s(W) :- \+ ns(W).
ns(Z) :- \+ l(Z,snow).
nl(X) :- \+ l(X).
nl(tony,U) :- l(mike,U).
l(tony,V) :- \+ l(mike,V).
