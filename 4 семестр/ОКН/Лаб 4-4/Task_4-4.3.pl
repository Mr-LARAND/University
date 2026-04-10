digits(N, Digits) :-
    number_chars(N, Chars),
    maplist(atom_number, Chars, Digits).