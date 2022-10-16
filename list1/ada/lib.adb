with Interfaces.C; use Interfaces.C;
with Ada.Text_IO; use Ada.Text_IO;

package body lib is 

  function factorial(n : unsigned_long) return unsigned_long is
    result : unsigned_long := 1;
  begin
    if (n = 0) then
      return 1;
    end if;
    
    for i in 2..n loop
      result := result * i;
    end loop;

    return result;
  end factorial;

  function rec_factorial(n : unsigned_long) return unsigned_long is
  begin
    if (n = 0) then
      return 1;
    end if;

    return n * rec_factorial(n - 1);
  end rec_factorial;

  function gcd(x : unsigned_long; y : unsigned_long) return unsigned_long is
    result : unsigned_long := 1;
    minimum : unsigned_long := 1;
  begin
    if (x = 0 or y = 0) then
      return 0;
    end if;

    if (x = 1 or y = 1) then
      return 1;
    end if;

    if (x <= y) then
      minimum := x;
    else
      minimum := y;
    end if;

    for i in 1..minimum loop
      if (x mod i = 0 and y mod i = 0) then
        result := i;
      end if;
    end loop;

    return result;
  end gcd;

  function rec_gcd(x : unsigned_long; y : unsigned_long) return unsigned_long is
  begin
    if (y /= 0) then
      return rec_gcd(y, x mod y);
    end if;

    return x;
  end rec_gcd;

  function gcd_extended(a: Long_Long_Integer; b : Long_Long_Integer) return arr is
    prevx : Long_Long_Integer := 1;
    x : Long_Long_Integer := 0;
    prevy : Long_Long_Integer := 0;
    y : Long_Long_Integer := 1;

    a1 : Long_Long_Integer := a;
    b1 : Long_Long_Integer := b;
    q : Long_Long_Integer;
    temp : Long_Long_Integer;

    my_arr : arr;

  begin
    while (b1 /= 0) loop
      q := Long_Long_Integer(a1) / Long_Long_Integer(b1);
      temp := x;
      x := prevx - q * temp;
      prevx := temp;

      temp := y;
      y := prevy - q * temp;
      prevy := temp;

      temp := a1;
      a1 := b1;
      b1 := temp mod b1;
    end loop;

    my_arr := (a1, prevx, prevy);

    return my_arr;
  end gcd_extended;

  function rec_gcd_extended(a : Long_Long_Integer; b : Long_Long_Integer) return arr is
    gcd : Long_Long_Integer;
    x : Long_Long_Integer; x1 : Long_Long_Integer;
    y : Long_Long_Integer; y1 : Long_Long_Integer;

    my_arr : arr;
  begin
    if (a = 0) then
      my_arr := (b, 0, 1);
      return my_arr;
    end if;

    my_arr := rec_gcd_extended(b mod a, a);
    gcd := my_arr(1);
    x1 := my_arr(2);
    y1 := my_arr(3);

    x := y1 - (Long_Long_Integer(b) / Long_Long_Integer(a)) * x1;
    y := x1;

    my_arr := (gcd, x, y);
    return my_arr;
  end rec_gcd_extended;

  procedure diophantine_equation(a : Long_Long_Integer; b : Long_Long_Integer; c : Long_Long_Integer; x : out Long_Long_Integer; y : out Long_Long_Integer) is
    gcd_temp : Long_Long_Integer;
    x1 : Long_Long_Integer;
    y1 : Long_Long_Integer;

    my_arr : arr;
  begin
    if (a = 0 and b = 0) then
      if (c = 0) then
        x := 1;
        y := 1;
        return;
      else
        Put_Line("No possible solutions.");
        x := Long_Long_Integer'First;
        y := Long_Long_Integer'First;
        return;
      end if;
    end if;

    my_arr := gcd_extended(a, b);
    gcd_temp := my_arr(1);
    x1 := my_arr(2);
    y1 := my_arr(3);

    if (c mod gcd_temp /= 0) then
      Put_Line("No possible solutions.");
      x := Long_Long_Integer'First;
      y := Long_Long_Integer'First;
      return;
    end if;

    x := x1 * Long_Long_Integer(c) / Long_Long_Integer(gcd_temp);
    y := y1 * Long_Long_Integer(c) * Long_Long_Integer(gcd_temp);

    return;
  end diophantine_equation;

  procedure rec_diophantine_equation(a : Long_Long_Integer; b : Long_Long_Integer; c : Long_Long_Integer; x : out Long_Long_Integer; y : out Long_Long_Integer) is
    gcd_temp : Long_Long_Integer;
    x1 : Long_Long_Integer;
    y1 : Long_Long_Integer;

    my_arr : arr;
  begin
    if (a = 0 and b = 0) then
      if (c = 0) then
        x := 1;
        y := 1;
        return;
      else
        Put_Line("No possible solutions.");
        x := Long_Long_Integer'First;
        y := Long_Long_Integer'First;
        return;
      end if;
    end if;

    my_arr := rec_gcd_extended(a, b);
    gcd_temp := my_arr(1);
    x1 := my_arr(2);
    y1 := my_arr(3);

    if (c mod gcd_temp /= 0) then
      Put_Line("No possible solutions.");
      x := Long_Long_Integer'First;
      y := Long_Long_Integer'First;
      return;
    end if;

    x := x1 * Long_Long_Integer(c) / Long_Long_Integer(gcd_temp);
    y := y1 * Long_Long_Integer(c) * Long_Long_Integer(gcd_temp);

    return;
  end rec_diophantine_equation;

  procedure diophantine_equation_test is 
    dimension : Integer := 7;
    type arrr is array (1..dimension) of arr;
    my_arr : arrr := ((13, 5, 1), (27, 4, 3), (15, 5, 25), (1, 1, 1), (0, 0, 0), (0, 0, 1), (0, 1, 0));

    x : aliased Long_Long_Integer; y : aliased Long_Long_Integer;
    a : Long_Long_Integer; b : Long_Long_Integer; c : Long_Long_Integer;
  begin
    Put_Line("================ [DIOPHANTINE  EQUASION] ================");
    for i in 1..dimension loop
      a := my_arr(i)(1); 
      b := my_arr(i)(2); 
      c := my_arr(i)(3);

      Put_Line(ASCII.LF & "Diophantine equation for a =" & Long_Long_Integer'Image(a) & ", b =" & Long_Long_Integer'Image(b) & ", c =" & Long_Long_Integer'Image(c) & ASCII.LF);
      Put_Line("Iterative algorithm:");

      diophantine_equation(a, b, c, x, y);

      if (x /= Long_Long_Integer'First) then
        Put_Line("Solution found!");
        Put_Line(Long_Long_Integer'Image(a) & " *" & Long_Long_Integer'Image(x) & " +"  & Long_Long_Integer'Image(b) & " *" & Long_Long_Integer'Image(y) & " =" & Long_Long_Integer'Image(c) & ASCII.LF);
      end if;

      Put_Line("Recursive algorithm:");
      rec_diophantine_equation(a, b, c, x, y);

      if (x /= Long_Long_Integer'First) then
        Put_Line("Solution found!");
        Put_Line(Long_Long_Integer'Image(a) & " *" & Long_Long_Integer'Image(x) & " +"  & Long_Long_Integer'Image(b) & " *" & Long_Long_Integer'Image(y) & " =" & Long_Long_Integer'Image(c) & ASCII.LF);
      end if;

      Put_Line("---------------------------------------------------------");
    end loop;
  end diophantine_equation_test;
end lib;
