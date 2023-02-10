/*  
  javac Main.java GaloisField.java Polynomial.java RealNumber.java
  java -ea Main
*/
import java.util.ArrayList;

class Main {

  static final long TEST_PRIME = 2;

  private static void constructor_test() {
    System.out.println("CONSTRUCTOR TESTS:");
    Polynomial<GaloisField> p = new Polynomial<GaloisField>(new GaloisField(1, TEST_PRIME));

    System.out.println("   p.get_degree() == 0");
    assert (p.get_degree() == 0);

    System.out.println("   p.get_coeff(0)._get_number() == 1");
    assert (p.get_coeff(0)._get_number() == 1);

    System.out.println("   p.get_coeff(0)._get_order() == 2");
    assert (p.get_coeff(0)._get_order() == 2);

    Polynomial<RealNumber> q = new Polynomial<RealNumber>(new RealNumber(1));

    System.out.println("   q.get_degree() == 0");
    assert (q.get_degree() == 0);

    System.out.println("   q.get_coeff(0)._get_number() == 1");
    assert (q.get_coeff(0)._get_number() == 1);

    ArrayList<RealNumber> coefficients = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients.add(new RealNumber(i + 0.5));
    }

    Polynomial<RealNumber> r = new Polynomial<RealNumber>(coefficients);

    System.out.println("   r.get_degree() == 9");
    assert (r.get_degree() == 9);

    for (int i = 0; i < 10; i++) {
      System.out.println("   r.get_coeff(" + i + ")._get_number() == " + (i + 0.5));
      assert (r.get_coeff(i)._get_number() == (i + 0.5));
    }

    Polynomial<RealNumber> s = new Polynomial<RealNumber>(r);

    System.out.println("   s.get_degree() == 9");
    assert (s.get_degree() == 9);

    System.out.println("   r == s");
    assert (r.equals(s));

    System.out.println("  TESTS PASSED!");
  }
  
  private static void add_test() {
    System.out.println("\nADD TESTS:");
    ArrayList<GaloisField> coefficients = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients.add(new GaloisField(i, TEST_PRIME));
    }
    ArrayList<GaloisField> coefficients2 = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients2.add(new GaloisField(i + 1, TEST_PRIME));
    }

    Polynomial<GaloisField> p = new Polynomial<GaloisField>(coefficients);
    Polynomial<GaloisField> q = new Polynomial<GaloisField>(coefficients2);

    Polynomial<GaloisField> r = p._add(q);
 
    System.out.println("   r.get_degree() == 9");
    assert (r.get_degree() == 9);

    for (int i = 0; i < 10; i++) 
    {
      System.out.println("   r.get_coeff(" + i + ")._get_number() == " + ((i + i + 1) % TEST_PRIME));
      assert (r.get_coeff(i)._get_number() == (i + i + 1) % TEST_PRIME);
    }
    
    ArrayList <RealNumber> coefficients3 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients3.add(new RealNumber(i + 0.5));
    }

    ArrayList<RealNumber> coefficients4 = new ArrayList<RealNumber>();
    
    for (int i = 0; i < 10; i++) {
      coefficients4.add(new RealNumber(i + 1.5));
    }

    Polynomial<RealNumber> s = new Polynomial<RealNumber>(coefficients3);
    Polynomial<RealNumber> t = new Polynomial<RealNumber>(coefficients4);

    Polynomial<RealNumber> u = s._add(t);

    System.out.println("   u.get_degree() == 9");
    assert (u.get_degree() == 9);

    for (int i = 0; i < 10; i++) 
    {
      System.out.println("   u.get_coeff(" + i + ")._get_number() == " + (i + i + 2));
      assert (u.get_coeff(i)._get_number() == (i + i + 2));
    }

    System.out.println("  TESTS PASSED!");
  }

  private static void sub_test() {
    System.out.println("\nSUB TESTS:");
    ArrayList<GaloisField> coefficients = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients.add(new GaloisField(i, TEST_PRIME));
    }

    ArrayList<GaloisField> coefficients2 = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients2.add(new GaloisField(i + 1, TEST_PRIME));
    }

    Polynomial<GaloisField> p = new Polynomial<GaloisField>(coefficients);
    Polynomial<GaloisField> q = new Polynomial<GaloisField>(coefficients2);

    Polynomial<GaloisField> r = p.sub(q);

    System.out.println("   r.get_degree() == 9");
    assert (r.get_degree() == 9);

    for (int i = 0; i < 10; i++) 
    {
      System.out.println(
          "   r.get_coeff(" + i + ")._get_number() == " + ((i - i - 1 + TEST_PRIME) % TEST_PRIME));
      assert (r.get_coeff(i)._get_number() == (i - i - 1 + TEST_PRIME) % TEST_PRIME);
    }
    
    ArrayList<RealNumber> coefficients3 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients3.add(new RealNumber(i + 0.5));
    }
    
    ArrayList<RealNumber> coefficients4 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients4.add(new RealNumber(i + 1.5));
    }

    Polynomial<RealNumber> s = new Polynomial<RealNumber>(coefficients3);
    Polynomial<RealNumber> t = new Polynomial<RealNumber>(coefficients4);

    Polynomial<RealNumber> u = s.sub(t);

    System.out.println("   u.get_degree() == 9");
    assert (u.get_degree() == 9);

    for (int i = 0; i < 10; i++) 
    {
      System.out.println("   u.get_coeff(" + i + ")._get_number() == " + (i - i - 1));
      assert (u.get_coeff(i)._get_number() == (i - i - 1));
    }

    System.out.println("  TESTS PASSED!");
  }

  private static void mul_test() {
    System.out.println("\nMUL TESTS:");
    ArrayList<GaloisField> coefficients = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients.add(new GaloisField(i, TEST_PRIME));
    }

    ArrayList<GaloisField> coefficients2 = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients2.add(new GaloisField(i + 1, TEST_PRIME));
    }

    Polynomial<GaloisField> p = new Polynomial<GaloisField>(coefficients);
    Polynomial<GaloisField> q = new Polynomial<GaloisField>(coefficients2);

    Polynomial<GaloisField> r = p.mul(q);

    System.out.println("   r.get_degree() == 9");
    assert (r.get_degree() == 9);

    for (int i = 0; i < r.get_degree(); i++) 
    {
      System.out.println("   r.get_coeff(" + i + ")._get_number() == " + (i * i % TEST_PRIME));
      assert (r.get_coeff(i)._get_number() == (i * i % TEST_PRIME));
    }

    ArrayList<RealNumber> coefficients3 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients3.add(new RealNumber(i + 0.5));
    }

    ArrayList<RealNumber> coefficients4 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients4.add(new RealNumber(i + 1.5));
    }

    Polynomial<RealNumber> s = new Polynomial<RealNumber>(coefficients3);
    Polynomial<RealNumber> t = new Polynomial<RealNumber>(coefficients4);

    Polynomial<RealNumber> u = s.mul(t);

    System.out.println("   u.get_degree() == 18");
    assert (u.get_degree() == 18);

    System.out.println("  TESTS PASSED!");
  }

  private static void div_test() {
    System.out.println("\nDIV TESTS:");
    ArrayList<GaloisField> coefficients = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients.add(new GaloisField(i, TEST_PRIME));
    }

    ArrayList<GaloisField> coefficients2 = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients2.add(new GaloisField(i + 1, TEST_PRIME));
    }

    Polynomial<GaloisField> p = new Polynomial<GaloisField>(coefficients);
    Polynomial<GaloisField> q = new Polynomial<GaloisField>(coefficients2);

    Polynomial<GaloisField> r = p.div(q);

    System.out.println("   r.get_degree() == 0");
    assert (r.get_degree() == 0);

    System.out.println("   r.get_coeff(0)._get_number() == 0");

    assert (r.get_coeff(0)._get_number() == 0);

    ArrayList<RealNumber> coefficients3 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients3.add(new RealNumber(i + 0.5));
    }

    ArrayList<RealNumber> coefficients4 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients4.add(new RealNumber(i + 1.5));
    }

    Polynomial<RealNumber> s = new Polynomial<RealNumber>(coefficients3);
    Polynomial<RealNumber> t = new Polynomial<RealNumber>(coefficients4);

    Polynomial<RealNumber> u = s.div(t);

    System.out.println("   u.get_degree() == 0");
    assert (u.get_degree() == 0);

    System.out.println("  TESTS PASSED!");
  }

  private static void comparisons_test() {
    System.out.println("\nCOMPARISONS TESTS:");
    ArrayList<GaloisField> coefficients = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients.add(new GaloisField(i, TEST_PRIME));
    }

    ArrayList<GaloisField> coefficients2 = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients2.add(new GaloisField(i + 1, TEST_PRIME));
    }

    Polynomial<GaloisField> p = new Polynomial<GaloisField>(coefficients);
    Polynomial<GaloisField> q = new Polynomial<GaloisField>(coefficients2);

    System.out.println("   p.equals(q) == false");
    assert (p.equals(q) == false);

    System.out.println("   p.equals(p) == true");
    assert (p.equals(p) == true);

    System.out.println("   p.lt(q) == true");
    assert (p.lt(q) == false);

    System.out.println("   p.gt(q) == false");
    assert (p.gt(q) == true);

    System.out.println("   p.le(q) == true");
    assert (p.le(q) == false);

    System.out.println("   p.ge(q) == false");
    assert (p.ge(q) == true);

    ArrayList<RealNumber> coefficients3 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients3.add(new RealNumber(i + 0.5));
    }

    ArrayList<RealNumber> coefficients4 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients4.add(new RealNumber(i + 1.5));
    }

    Polynomial<RealNumber> s = new Polynomial<RealNumber>(coefficients3);
    Polynomial<RealNumber> t = new Polynomial<RealNumber>(coefficients4);

    System.out.println("   s.equals(t) == false");
    assert (s.equals(t) == false);

    System.out.println("   s.equals(s) == true");
    assert (s.equals(s) == true);

    System.out.println("   s.lt(t) == true");
    assert (s.lt(t) == true);

    System.out.println("   s.gt(t) == false");
    assert (s.gt(t) == false);

    System.out.println("   s.le(t) == true");
    assert (s.le(t) == true);

    System.out.println("   s.ge(t) == false");
    assert (s.ge(t) == false);

    System.out.println("  TESTS PASSED!");
  }

  private static void value_test() {
    System.out.println("\nVALUE TESTS:");
    ArrayList<GaloisField> coefficients = new ArrayList<GaloisField>();
    for (int i = 0; i < 10; i++) {
      coefficients.add(new GaloisField(i, TEST_PRIME));
    }

    Polynomial<GaloisField> p = new Polynomial<GaloisField>(coefficients);
    GaloisField x = new GaloisField(2, TEST_PRIME);
    GaloisField y = p.value(x);

    System.out.println("   y._get_number() == 0");
    assert (y._get_number() == 0);

    ArrayList<RealNumber> coefficients2 = new ArrayList<RealNumber>();
    for (int i = 0; i < 10; i++) {
      coefficients2.add(new RealNumber(i + 0.5));
    }

    Polynomial<RealNumber> q = new Polynomial<RealNumber>(coefficients2);
    RealNumber x2 = new RealNumber(2.0);
    RealNumber y2 = q.value(x2);

    System.out.println("   y2._get_number() == 1.0");
    assert (y2._get_number() == 8705.5);

    System.out.println("  TESTS PASSED!");
  }
  
  public static void main(String[] args) {
    System.out.println("TESTING GALOIS FIELD IMPLEMENTATION ON p=" + TEST_PRIME);
    System.out.println("f=GF(" + TEST_PRIME + ")" );
    System.out.println("TEST: constructor");
    constructor_test();
    System.out.println("TEST: add" );
    add_test();
    System.out.println("TEST: sub" );
    sub_test();
    System.out.println("TEST: mul" );
    mul_test();
    System.out.println("TEST: div" );
    div_test();
    comparisons_test();

    value_test();
  }
}
