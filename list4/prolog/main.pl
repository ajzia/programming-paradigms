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

gcd_extended(A, 0, A, 1, 0) :- !.
gcd_extended(A, B, G, X, Y) :-
  B > 0,
  B1 is A mod B,
  gcd_extended(B, B1, G, X1, Y1),
  X is Y1,
  Y is X1 - (A div B) * Y1.

diophantine_equation(0, 0, 0, 1, 1) :- !.
diophantine_equation(0, 0, C, _, _) :- 
  C \= 0, !, fail.
diophantine_equation(A, B, C, X, Y) :-
  gcd_extended(A, B, G, X1, Y1),
  0 is C mod G,
  C1 is C div G,
  X is X1 * C1,
  Y is Y1 * C1.
