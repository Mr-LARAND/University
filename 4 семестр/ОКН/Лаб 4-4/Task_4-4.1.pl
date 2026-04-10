remove_three(List, Result) :-
    length(Prefix, 3),
    append(Prefix, Rest, List),
    append(Result, Suffix, Rest),
    length(Suffix, 3).