factorial(0, 1) :- !.
factorial(1, 1) :- !.
factorial(N, X) :- 
  N > 0, 
  N1 is N - 1, 
  factorial(N1, X1), 
  X is N * X1.

gcd(X, 0, X) :- !.
gcd(X, Y, G) :-
  Y > 0,
  X1 is X mod Y,
  gcd(Y, X1, G).

rec_gcd_extended(0, _, 0, 1) :- !.
rec_gcd_extended(A, B, X, Y) :-
  A1 is B mod A,
  rec_gcd_extended(A1, A, X1, Y1),
  X is Y1 - (B div A) * X1,
  Y is X1.

diophantine_equation(0, _, 0, 1, _) :- !.
diophantine_equation(A, B, C, X, Y) :-
  gcd(A, B, G),
  C mod G =:= 0,
  A1 is A div G,
  B1 is B div G,
  C1 is C div G,
  rec_gcd_extended(A1, B1, X1, Y1),
  X is X1 * C1,
  Y is Y1 * C1.
