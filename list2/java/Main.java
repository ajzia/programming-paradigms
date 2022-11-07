/*  
  javac Main.java GaloisField.java
  java -ea Main
  -ea (enable assertions)
*/
class Main {
  public static void main(String[] args) {
    constructor_test();
    arithmetic_test();
    incrementation_test();
    comparison_test();
  }

  static final long TEST_PRIME = 1234567891;

  static long mod(long number, long mod) {
    return ((((number + mod) % mod) + mod) % mod);
  }

  static long gen_number() {
    return (long) ((Math.random() * (TEST_PRIME - (-TEST_PRIME))) + (-TEST_PRIME));
  }

  static void constructor_test() {
    System.out.println("CONSTRUCTOR TESTS:");
  
    final long x = Math.abs(gen_number());
    GaloisField gf1 = new GaloisField(x, TEST_PRIME);
    GaloisField gf2 = new GaloisField(-1, TEST_PRIME);
  
    System.out.println("   positive number test:");
    System.out.println("     " + gf1 + ".number == " + mod(x, TEST_PRIME));
    assert(gf1.get_number() == mod(x, TEST_PRIME));
    System.out.println("     " + gf1 + ".order == " + TEST_PRIME);
    assert(gf1.get_order() == TEST_PRIME);
  
    System.out.println("\n   negative number test:");
    System.out.println("     " + "GF<" + TEST_PRIME + ">(-1).number" + " == " + mod(-1, TEST_PRIME));
    assert(gf2.get_number() == mod(-1, TEST_PRIME));
    System.out.println("     " + gf2 + ".order == " + TEST_PRIME);
    assert(gf2.get_order() == TEST_PRIME);
  
    System.out.println("  TESTS PASSED!");
  }

  static void arithmetic_test() {
    System.out.println("\nARITHMETIC TESTS:");
  
    final long x = Math.abs(gen_number()), y = Math.abs(gen_number());
    GaloisField gf1 = new GaloisField(x, TEST_PRIME);
    GaloisField gf2 = new GaloisField(y, TEST_PRIME);
  
    System.out.println("     + test:");
    System.out.println("       [" + gf1 + " + " + gf2 + "].get_number() == " + mod(gf1.get_number() + gf2.get_number(), TEST_PRIME) );
    assert(mod(gf1.get_number() + gf2.get_number(), TEST_PRIME) == (gf1._add(gf2)).get_number());

    System.out.println("\n     - test:");
    System.out.println("       [" + gf1 + " - " + gf2 + "].get_number() == " + mod(gf1.get_number() - gf2.get_number(), TEST_PRIME) );
    assert(mod(gf1.get_number() - gf2.get_number(), TEST_PRIME) == (gf1._sub(gf2)).get_number());

    System.out.println("\n     * test:");
    System.out.println("       [" + gf1 + " * " + gf2 + "].get_number() == " + mod(gf1.get_number() * gf2.get_number(), TEST_PRIME) );
    assert(mod(gf1.get_number() * gf2.get_number(), TEST_PRIME) == (gf1._mul(gf2)).get_number());

  
    System.out.println("\n     / test:");
    System.out.println("       [" + gf1 + " / " + gf2 + "].get_number() == " + mod(gf1.get_number() * gf2.mod_inverse().get_number(), TEST_PRIME) );
    assert(mod(gf1.get_number() * gf2.mod_inverse().get_number(), TEST_PRIME) == (gf1._div(gf2)).get_number());
    GaloisField temp = gf1;
    assert((gf1._div(gf2))._mul(gf1._mul(gf2)) == (temp._mul(temp)));

    System.out.println("  TESTS PASSED!");
  }
  
  static void incrementation_test() {
    System.out.println("\nINCREMENTATION TESTS:");

    final long x = Math.abs(gen_number()), y = Math.abs(gen_number());
    GaloisField gf1 = new GaloisField(x, TEST_PRIME);
    GaloisField gf2 = new GaloisField(y, TEST_PRIME);
  
    System.out.println("     ++ test:");
    System.out.println("       [" + gf2 + "++] == [" + gf2 + " + 1]");
    gf1 = gf2;
    gf2._inc();
    assert(gf2 == (gf1._add(1)));
  
    System.out.println("\n     -- test:");
    System.out.println("       [" + gf2 + "--] == [" + gf2 + " - 1]");
    gf1 = gf2;
    gf2._dec();
    assert(gf2 == (gf1._sub(1)));
  
    System.out.println("  TESTS PASSED!");
  }

  static void comparison_test() {
    System.out.println("\nCOMPARISON TESTS:");

    final long x = Math.abs(gen_number()), y = Math.abs(gen_number());
    GaloisField gf1 = new GaloisField(x, TEST_PRIME);
    GaloisField gf2 = new GaloisField(y, TEST_PRIME);
    GaloisField gf3 = new GaloisField(0, TEST_PRIME);
    GaloisField gf4 = new GaloisField(TEST_PRIME + 1, TEST_PRIME);
  
    System.out.println("     < tests:");
    System.out.println("       [" + gf1 + " < " + gf2 + "] == " + "[" + mod(x, TEST_PRIME) + " < " + mod(y, TEST_PRIME) + "]");
    assert((gf1._lt(gf2)) == (mod(x, TEST_PRIME) < mod(y, TEST_PRIME)));
    System.out.println("       [" + gf3 + " < GF<1234567891>(1234567891 + 1)]");
    assert(gf3._lt(gf4));
  
    System.out.println("\n     > tests:");
    System.out.println("       [" + gf1 + " > " + gf2 + "] == " + "[" + mod(x, TEST_PRIME) + " > " + mod(y, TEST_PRIME) + "]");
    assert((gf1._gt(gf2)) == (mod(x, TEST_PRIME) > mod(y, TEST_PRIME)));
    System.out.println("       [" + (gf3._add(2)) + " > GF<1234567891>(1234567891 + 1)]");
    assert(gf3._gt(gf4));
  
    System.out.println("\n     <= tests:");
    System.out.println("       [" + gf1 + " <= " + gf2 + "] == " + "[" + mod(x, TEST_PRIME) + " <= " + mod(y, TEST_PRIME) + "]");
    assert((gf1._le(gf2)) == (mod(x, TEST_PRIME) <= mod(y, TEST_PRIME)));
    System.out.println("       [" + gf3 + " <= GF<1234567891>(1234567891 + 1)]");
    gf3._dec();
    assert(gf3._le(gf4));
  
    System.out.println("\n     >= tests:");
    System.out.println("       [" + gf1 + " >= " + gf2 + "] == " + "[" + mod(x, TEST_PRIME) + " >= " + mod(y, TEST_PRIME) + "]");
    assert((gf1._ge(gf2)) == (mod(x, TEST_PRIME) >= mod(y, TEST_PRIME)));
    System.out.println("       [" + gf3 + " <= GF<1234567891>(1234567891 + 1)]");
    assert(gf3._ge(gf4));
  
    System.out.println("\n     == tests:");
    System.out.println("       [" + gf1 + " == " + gf2 + "] == " + "[" + mod(x, TEST_PRIME) + " == " + mod(y, TEST_PRIME) + "]");
    assert((gf1._eq(gf2)) == (mod(x, TEST_PRIME) == mod(y, TEST_PRIME)));
    System.out.println("       [" + gf3 + " == GF<1234567891>(1234567891 + 1)]");
    assert(gf3._eq(gf4));
  
    System.out.println("\n     != tests:");
    System.out.println("       [" + gf1 + " != " + gf2 + "] == " + "[" + mod(x, TEST_PRIME) + " != " + mod(y, TEST_PRIME) + "]");
    assert((gf1._neq(gf2)) == (mod(x, TEST_PRIME) != mod(y, TEST_PRIME)));
    gf3._dec();
    System.out.println("       [" + gf3 + " != GF<1234567891>(1234567891 + 1)]");
    assert(gf3._neq(gf4)); 
  
    System.out.println("\n     = tests:");
    long n = 1537;
    gf1._assign(n);
    System.out.println("       [" + gf1 + " = ("+ n + ")] == GF<" + gf1.get_order() + ">(" + mod(n, TEST_PRIME) + ")");
    assert((gf1).get_number() == mod(n, TEST_PRIME)); 
    n = -1;
    System.out.println("       [" + gf1 + " = ("+ n + ")] == GF<" + gf1.get_order() + ">(" + mod(n, TEST_PRIME) + ")");
    gf1._assign(n);
    assert(gf1.get_number() == mod(n, TEST_PRIME)); 
  
    System.out.println("  TESTS PASSED!");
  }
}
