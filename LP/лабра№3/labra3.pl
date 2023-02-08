calculate(EXP, SOL):-
    reverse(EXP, EXP1), a_exp(EXP1, SOL), !.
a_number([NS],NS):- number(NS).
a_term(T,V):- a_number(T,V).
a_term(T,V):-
    append(X,['*'|Y],T),
    a_number(X,Vx),
    a_term(Y,Vy),
    V = ['*',Vy,Vx].
a_term(T,V):- append(X,[':'|Y],T),
    a_number(X,Vx),
    a_term(Y,Vy),
    V = [':',Vx,Vy].
a_exp(T,V):- a_term(T,V).
a_exp(T,V):- append(X,['+'|Y],T),
    a_term(X,Vx),
    a_exp(Y,Vy),
    V = ['+',Vy,Vx].
a_exp(T,V):- append(X,['-'|Y],T),
    a_term(X,Vx),
    a_exp(Y,Vy),
    V = ['-',Vx,Vy].

