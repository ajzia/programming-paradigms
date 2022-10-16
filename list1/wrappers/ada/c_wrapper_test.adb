with Ada.Text_IO; use Ada.Text_IO;

package body c_wrapper_test is
  procedure diophantine_equation_test is 
    dimension : Integer := 7;
    type arr is array(1..3) of aliased Long_Long_Integer;
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

      diophantine_equation(a, b, c, x'Access, y'Access);

      if (x /= Long_Long_Integer'First) then
        Put_Line("Solution found!");
        Put_Line(Long_Long_Integer'Image(a) & " *" & Long_Long_Integer'Image(x) & " +"  & Long_Long_Integer'Image(b) & " *" & Long_Long_Integer'Image(y) & " =" & Long_Long_Integer'Image(c) & ASCII.LF);
      end if;

      Put_Line("Recursive algorithm:");
      rec_diophantine_equation(a, b, c, x'Access, y'Access);

      if (x /= Long_Long_Integer'First) then
        Put_Line("Solution found!");
        Put_Line(Long_Long_Integer'Image(a) & " *" & Long_Long_Integer'Image(x) & " +"  & Long_Long_Integer'Image(b) & " *" & Long_Long_Integer'Image(y) & " =" & Long_Long_Integer'Image(c) & ASCII.LF);
      end if;

      Put_Line("---------------------------------------------------------");
    end loop;
  end diophantine_equation_test;

end c_wrapper_test;
