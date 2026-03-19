% F(x) = x + sin(x²), при x <= 0
% F(x) = x + 58,     при 0 < x < 1

% Случай 1: X <= 0
calculate_f(X, F) :-
    X =< 0, !,
    F is X + sin(X*X).

% Случай 2: 0 < X < 1
calculate_f(X, F) :-
    X < 1, !,
    F is X + 58.