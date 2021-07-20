init_male(george).
init_male(andrew).
init_male(edward).
init_male(william).
init_male(harry).
init_male(peter).
init_male(james).
init_female(spencer).
init_female(elizabeth).
init_female(margaret).
init_female(diana).
init_female(anne).
init_female(zara).
init_female(beatrice).
init_female(eugenie).
init_female(louise).
init_female(charlotte).
init_child(elizabeth, george).
init_child(margaret, george).
init_child(diana, spencer).
init_child(charles, elizabeth).
init_child(anne, elizabeth).
init_child(andrew, elizabeth).
init_child(edward, elizabeth).
init_child(william, diana).
init_child(harry, diana).
init_child(peter, anne).
init_child(zara, anne).
init_child(beatrice, andrew).
init_child(eugenie, andrew).
init_child(louise, edward).
init_child(james, edward).
init_child(charlotte, william).
init_spouse(george, mum).
init_spouse(spencer, kydd).
init_spouse(elizabeth, philip).
init_spouse(diana, charles).
init_spouse(anne, mark).
init_spouse(andrew, sarah).
init_spouse(edward, sophie).
male(X) :- init_male(X); (spouse(X, Y), init_female(Y)).
female(X) :- init_female(X); (spouse(X, Y), init_male(Y)).
child(X, Y) :- init_child(X, Y); (init_child(X, Z), spouse(Y, Z)).
spouse(X, Y) :- init_spouse(X, Y); init_spouse(Y, X).
grandchild(X, Y) :- child(X, Z), child(Z, Y).
great_grandparent(X, Y) :- child(Y, Z), child(Z, A), child(A, X).
ancestor(X, Y) :- child(Y, X); (child(Y, Z), ancestor(X, Z)).
sibling(X, Y) :- child(X, Z), child(Y, Z), X \= Y.
brother(X, Y) :- sibling(X, Y), male(X).
sister(X, Y) :- sibling(X, Y), female(X).
dauter(X, Y) :- child(X, Y), female(X).
son(X, Y) :- child(X, Y), male(X).
first_cousin(X, Y) :- grandchild(X, Z), grandchild(Y, Z), \+ sibling(X, Y), X \= Y.
brother_in_law(X, Y) :- (sister(Z, Y), spouse(X, Z));
                        (spouse(Y, Z), brother(X, Z));
                        (spouse(Y, Z), sister(A, Z), spouse(X, A)).
sister_in_law(X, Y) :- (brother(Z, Y), spouse(X, Z));
                        (spouse(Y, Z), sister(X, Z));
                        (spouse(Y, Z), brother(A, Z), spouse(X, A)).
aunt(X, Y) :- (child(Y, Z), sister(X, Z)); (child(Y, Z), sister_in_law(X, Z)).
uncle(X, Y) :- (child(Y, Z), brother(X, Z)); (child(Y, Z), brother_in_law(X, Z)).
distance(X, Y, N) :- (X = Y, N = 0);
                        (ancestor(X, Y), child(Y, Z),
                        distance(X, Z, N1), N is N1 + 1);
                        (\+ ancestor(X, Y), ancestor(Z, X), ancestor(Z, Y),
                        distance(Z, Y, N1), distance(Z, X, N2), N is N1 - N2).
mth_cousin_n_removed(X, Y, M, N) :- distance(Z, X, N1), N1 is M + 1,
                                    distance(Z, Y, N2), N2 is M + N + 1,
                                    \+ (ancestor(Z, A), (ancestor(A, X); A = X), (ancestor(A, Y); A = Y)).