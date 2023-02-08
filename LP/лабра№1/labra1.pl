my_member(X,[X|T]).
my_member(X,[H|T]):- my_member(X,T).

my_append([], List2, List2).
my_append([Head|Tail], List2, [Head|TailResult]):-
   my_append(Tail, List2, TailResult).

my_length([], 0).
my_length([X|L], N):- my_length(L, M), N is M+1.

my_remove(X, [X|T], T).
my_remove(X, [Y|T], [Y|F]):-
    my_remove(X,T,F).

sub_start([], _List):-!.
sub_start([Head|TailSub], [Head|TailList]):-
   sub_start(TailSub, TailList).
my_sublist(Sub, List):-
   sub_start(Sub, List), !.
my_sublist(Sub, [_Head|Tail]):-
   my_sublist(Sub, Tail).

my_permute([],[]).
my_permute(L,[X|T]):-
    my_remove(X,L,R),my_permute(R,T).
/*Программа для 1-ого задания 1й вариант*/
remove_last([_], []).
remove_last([X|Xt], [X|WithoutLast]) :- 
    remove_last(Xt, WithoutLast).

/*Программа для 1-ого задания 2й вариант*/
last_remove(Y, X):-
    reverse(Y, Z),
    Z=[H|T],
    reverse(T, X).

/*Программа для 2-ого задания 1й вариант*/
number_of_even_element([],0).
number_of_even_element([H|Tail],C):-
    H mod 2=:=0,
    !,
    number_of_even_element(Tail,C1),
    C is C1+1.
number_of_even_element([_|Tail],C):-
    number_of_even_element(Tail,C).

/*Программа для 2-ого задания 2й вариант*/
number_of_element_even([],0).
number_of_element_even([H|Tail],C):-
    (H mod 10=:=0; H mod 10=:=2; H mod 10=:=4; H mod 10=:=6; H mod 10=:=8),
    !,
    number_of_element_even(Tail,C1),
    C is C1+1.
number_of_element_even([_|Tail],C):-
    number_of_element_even(Tail,C).

/*Содержательный пример: Замена первого элемента списка*/
change_first_element(X, Y, Z) :- reverse(Y, A), last_remove(A, B), my_append(B, [X], C), reverse(C, Z).

/*Программа для 2-ой части*/
:- ['one.pl'].

/*Таблица и средний балл по каждой из групп*/
table_of_group(X, L, R) :- bagof(Y, student(X, Y), L), all_marks(L, RES, N), R is RES/N.
all_marks([], RES, N) :- RES is 0, N is 0. 
all_marks([H|T], RES, N) :- midle_mark([H], ANS), all_marks(T, Y, K), N is K+1, RES is Y+ANS.
midle_mark([H|_], ANS) :- findall(Z, grade(H, _, Z), R), midle_mark_for_person(R, Sum, N), ANS is Sum/N.
midle_mark_for_person([], 0, 0).
midle_mark_for_person([H|T], Sum, N) :- midle_mark_for_person(T, Rest, C), Sum is H + Rest, N is C+1.

/*Список студентов не сдавших экзамен*/
no_exam_student(A, X) :- subject(Y,A), bagof(Z, grade(Z, Y, 2), X).

/*Кол-во несддавших студентов в каждой из групп*/
no_exam_student_in_group(X, C) :- bagof(Y, student(X, Y), L), no_exam_student_count(L, C).
no_exam_student_count([], 0).
no_exam_student_count([H|T], X) :- grade(H, _, 2) -> no_exam_student_count(T, N), X is N+1; no_exam_student_count(T, N), X is N.