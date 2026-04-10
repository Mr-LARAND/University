make_positive([], []).

make_positive([H|T], [H1|T1]) :-
    H < 0,
    H1 is -H,
    make_positive(T, T1).

make_positive([H|T], [H|T1]) :-
    H >= 0,
    make_positive(T, T1).