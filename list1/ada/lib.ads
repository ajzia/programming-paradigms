with Interfaces.C; use Interfaces.C;

package lib is
  type arr is array (1..3) of Long_Long_Integer;

  function factorial(n : unsigned_long) return unsigned_long with
    Export, 
    Convention => C, 
    External_Name => "factorial";
  function rec_factorial(n : unsigned_long) return unsigned_long with
    Export, 
    Convention => C, 
    External_Name => "rec_factorial";

  function gcd(x : unsigned_long; y : unsigned_long) return unsigned_long with
    Export, 
    Convention => C, 
    External_Name => "gcd";
  function rec_gcd(x : unsigned_long; y : unsigned_long) return unsigned_long with
    Export, 
    Convention => C, 
    External_Name => "rec_gcd";

  function gcd_extended(a: Long_Long_Integer; b : Long_Long_Integer) return arr;
  function rec_gcd_extended(a : Long_Long_Integer; b : Long_Long_Integer) return arr;

  procedure diophantine_equation(a : Long_Long_Integer; b : Long_Long_Integer; c : Long_Long_Integer; x : out Long_Long_Integer; y : out Long_Long_Integer) with
    Export, 
    Convention => C, 
    External_Name => "diophantine_equation";

  procedure rec_diophantine_equation(a : Long_Long_Integer; b : Long_Long_Integer; c : Long_Long_Integer; x : out Long_Long_Integer; y : out Long_Long_Integer) with
    Export,
    Convention => C,
    External_Name => "rec_diophantine_equation";

  procedure diophantine_equation_test;
    
end lib;
