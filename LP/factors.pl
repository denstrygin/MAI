factors(N,L) :-
    N > 1, !,
    between(2,N,Chislo),
    Rest is N mod Chislo,
    (Rest == 0 ->
         Next is N div Chislo,
         L = [Chislo|L1],
         factors(Next,L1),!).
factors(1,[]).