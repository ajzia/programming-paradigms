-- gcc -c ../../c/src/lib.c && gnatmake c_wrapper.adb -largs lib.o && rm *.ali
-- ./c_wrapper

with Interfaces.C; use Interfaces.C;
with Ada.Text_IO; use Ada.Text_IO;

with c_wrapper_test; use c_wrapper_test;

--  my_main.adb
procedure c_wrapper is
  a : unsigned_long := 6; b : unsigned_long := 27; c : unsigned_long := 51;
  
  --  Declare an Ada function spec for Get_Num, then use
  --  C function get_num for the implementation.
  function factorial(n : unsigned_long) return unsigned_long;
  pragma Import (C, factorial);

  function rec_factorial(n : unsigned_long) return unsigned_long;
  pragma Import (C, rec_factorial);

  function gcd(x : unsigned_long; y : unsigned_long) return unsigned_long;
  pragma Import (C, gcd);

  function rec_gcd(x : unsigned_long; y : unsigned_long) return unsigned_long;
  pragma Import (C, rec_gcd);

begin
  Put_Line("====================== [FACTORIAL] ======================" & ASCII.LF);

  Put_Line("Factorial:           " & unsigned_long'Image(factorial(a)));
  Put_Line("Factorial:           " & unsigned_long'Image(rec_factorial(a)) & ASCII.LF);


  Put_Line("========================= [GCD] =========================" & ASCII.LF);
  Put_Line("GCD for           a =" & unsigned_long'Image(b) & ", b =" & unsigned_long'Image(c) & ":" & unsigned_long'Image(gcd(b, c)));
  Put_Line("Recursive GCD for a =" & unsigned_long'Image(b) & ", b =" & unsigned_long'Image(c) & ":" & unsigned_long'Image(rec_gcd(b, c)) & ASCII.LF);

  diophantine_equation_test;

end c_wrapper;
