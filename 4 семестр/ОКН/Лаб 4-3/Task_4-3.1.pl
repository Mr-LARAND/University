
calculate_y(X, P, Z, Y) :- Y is max(max(X*X, Z*Z), P*P) + Z / P.