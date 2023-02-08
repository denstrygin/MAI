:- encoding(utf8).
solve([[Sergeev, 1, A, E, I], [Borisov, 0, B, F, J], [Lednev, 0, C, G, K], [Panin, 0, D, H, L]]):-
    Sergeev = 'Сергеев', Borisov = 'Борисов', Lednev = 'Леднев', Panin = 'Панин',
    for(A, 0, 4), for(B, 0, 4), for(C, 0, 4), for(D, 0, 4), for(E, 0, 4), for(F, 0, 4), for(G, 0, 4), for(H, 0, 4),
    for(I, 0, 4), for(J, 0, 4), for(L, 0, 4), for(K, 0, 4),
    SUM is A + B + C + D, SUM =:= 3,
    P1 is 1*5 + A*2 + E*1 + I*4,
    P2 is B*2 + F*1 + J*4,
    P3 is C*2 + G*1 + K*4,
    P4 is D*2 + H*1 + L*4,
    C1 is 1 + A + E + I,
    C2 is B + F + J,
    C3 is C + G + K,
    C4 is D + H + L,
    SUM2 is P1 + P2 + P3 + P4, SUM2 =:= 18,
    C1 < C4, C2 < C4, C3 < C4,
    P4 < P1, P4 < P2, P4 < P3,
    SUM3 is P1 + P3, SUM4 is P2 + P4, SUM3 =:= SUM4,
    P1 \= P2, P1 \= P3, P1 \= P4,
    P2 \= P3, P2 \= P4, P3 \= P4.
for(A, A, _).
for(X, A, B):- A < B, A1 is A + 1, for(X, A1, B).