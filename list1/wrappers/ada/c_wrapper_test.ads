package c_wrapper_test is
  procedure diophantine_equation(a : Long_Long_Integer; b : Long_Long_Integer; c : Long_Long_Integer; x : access Long_Long_Integer; y : access Long_Long_Integer);
  pragma Import (C, diophantine_equation);

  procedure rec_diophantine_equation(a : Long_Long_Integer; b : Long_Long_Integer; c : Long_Long_Integer; x : access Long_Long_Integer; y : access Long_Long_Integer);
  pragma Import (C, rec_diophantine_equation);
      
  procedure diophantine_equation_test;

end c_wrapper_test;
