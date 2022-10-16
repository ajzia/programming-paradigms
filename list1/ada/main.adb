-- gnatmake main.adb && rm *.o *.ali
-- ./main

with Interfaces.C; use Interfaces.C;
with Ada.Text_IO; use Ada.Text_IO;

with lib; use lib;

procedure main is
  a : unsigned_long := 6; b : unsigned_long := 27; c : unsigned_long := 51;
begin
  Put_Line("====================== [FACTORIAL] ======================" & ASCII.LF);

  Put_Line("Factorial:           " & unsigned_long'Image(factorial(a)));
  Put_Line("Factorial:           " & unsigned_long'Image(rec_factorial(a)) & ASCII.LF);


  Put_Line("========================= [GCD] =========================" & ASCII.LF);
  Put_Line("GCD for           a =" & unsigned_long'Image(b) & ", b =" & unsigned_long'Image(c) & ":" & unsigned_long'Image(gcd(b, c)));
  Put_Line("Recursive GCD for a =" & unsigned_long'Image(b) & ", b =" & unsigned_long'Image(c) & ":" & unsigned_long'Image(rec_gcd(b, c)) & ASCII.LF);

  diophantine_equation_test;

end main;
