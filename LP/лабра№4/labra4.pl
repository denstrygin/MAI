% Переходы между состояниями.
move(A,B) :- append(H, ['b','w'|T], A), append(H, ['w','b'|T], B).
move(A,B) :- append(H, ['w','b'|T], A), append(H, ['b','w'|T], B).

prolong([X|T], [Y,X|T]) :- move(X, Y), not(member(Y, [X|T])).

% Печать результата на экран.
print([_]).
print([H|T]) :- print(T), nl, write(H).

% Поиск в ширину.
bfs(X, Y) :- get_time(Time1), write(X), bdth([[X]], Y, Z), print(Z), get_time(Time2), Time is Time2 - Time1, nl, write('DFS time: '), write(Time), nl, !.
bdth([[H|T]|_], H, [H|T]).
bdth([H|T], X, Z) :- findall(W, prolong(H, W), Y), append(T, Y, E), !, bdth(E, X, Z).
bdth([_,T], X, Y) :- bdth(T, X, Y).

% Поиск в глубину.
dfs(X, Y) :- get_time(Time1), write(X), ddth([[X]], Y, Z), print(Z), get_time(Time2), Time is Time2 - Time1, nl, write('BFS time: '), write(Time), nl, !.
ddth([[H|T]|_], H, [H|T]).
ddth([H|T], X, Z) :- findall(W, prolong(H, W), Y), append(Y, T, E), !, ddth(E, X, Z).
ddth([_,T], X, Y) :- ddth(T, X, Y).

% Поиск с итерационным погружением.
search_id(X, Y, W, D) :- depth_id([X], Y, W, D).
depth_id([H|T], H, [H|T], 0).
depth_id(W, X, Y, N) :- N>0, prolong(W, NEWW), N1 is N-1, depth_id(NEWW, X, Y, N1).
search_id(X, Y, W) :- integer(LEV), search_id(X, Y, W, LEV).
search_id(X, Y) :- get_time(Time1), write(X), search_id(X, Y, Z), print(Z), get_time(Time2), Time is Time2 - Time1, nl, write('DFS time: '), write(Time), nl, !.
integer(1).
integer(N) :- integer(N1), N is N1+1.