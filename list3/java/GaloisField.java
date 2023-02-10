public class GaloisField implements FieldElement<GaloisField> {
  private long number;
  private long order;

  GaloisField(final long number, final long order) {
    try {
      if (is_prime(order)) {
        this.number = ((((number + order) % order) + order) % order);
        this.order = order;
      } else {
        throw new PrimeException();
      }
      
    } catch (PrimeException e) {
      StackTraceElement frame = new Exception().getStackTrace()[0];
      System.err.println("\n" + frame.getFileName() + ":" + frame.getLineNumber() + ": " + e.getMessage());
      System.exit(0);
    }
  }

  // Arithmetic
  public GaloisField _add(final GaloisField gf) {
    this.number = (((this.number + gf.number + this.order) % this.order) + this.order) % this.order;
    return this;
  }
 
  public GaloisField _add(final long number) {
    this.number = (((this.number + number + this.order) % this.order) + this.order) % this.order;
    return this;
  }

  public GaloisField _sub(final GaloisField gf) {
    this.number = (((this.number - gf.number + this.order) % this.order) + this.order) % this.order;
    return this;
  }
  
  public GaloisField _sub(final long number) {
    this.number = (((this.number - number + this.order) % this.order) + this.order) % this.order;
    return this;
  }

  public GaloisField _mul(final GaloisField gf) {
    this.number = (((this.number * gf.number + this.order) % this.order) + this.order) % this.order;
    return this;
  }
  
  public GaloisField _mul(final long number) {
    this.number = (((this.number * number + this.order) % this.order) + this.order) % this.order;
    return this;
  }

  public GaloisField _div(final GaloisField gf) {
    this._mul(gf._inv());
    return this;
  }

  public GaloisField _div(final long number) {
    this._mul((new GaloisField(number, order))._inv());
    return this;
  }

  // Incrementation
  public void _inc() {
    this.number++;
  }

  public void _dec() {
    this.number--;
  }

  // Comparison
  public boolean _eq(final GaloisField gf) {
    return (this.number == gf.number);
  }

  public boolean _neq(final GaloisField gf) {
    return (this.number != gf.number);
  }

  public boolean _gt(final GaloisField gf) {
    return (this.number > gf.number);
  }

  public boolean _lt(final GaloisField gf) {
    return (this.number < gf.number);
  }

  public boolean _ge(final GaloisField gf) {
    return (this.number >= gf.number);
  }

  public boolean _le(final GaloisField gf) {
    return (this.number <= gf.number);
  }

  // Assignment
  public GaloisField _assign(final long number) {
    this.number = (((number + this.order) % this.order) + this.order) % this.order;
    return this;
  }

  // Equals
  public boolean equals(Object compareObj) {
    if (this == compareObj)
      return true;

    if (!(compareObj instanceof GaloisField))
      return false;

    GaloisField compared = (GaloisField) compareObj;
    if (this.order != compared.order)
      return false;
    if (this.number != compared.number)
      return false;

    return true;
  }

  public GaloisField _neg() {
    return new GaloisField(-this.number, this.order);
  }

  public GaloisField _one() {
    return new GaloisField(1, this.order);
  }

  public GaloisField _zero() {
    return new GaloisField(0, this.order);
  }

  public boolean _isZero() {
    return this.number == 0;
  }

  public boolean _isOne() {
    return this.number == 1;
  }

  // Print
  public String toString() {
    return ("GF<" + this.order + ">(" + this.number + ")");
  }

  // Modular inverse
  private static long mod_inv(final long a, final long b, final long x, final long y) {
    return b == 0 ? x : mod_inv(b, a % b, y, x - y * (a / b));
  }

  public GaloisField _inv() {
    return new GaloisField(mod_inv(this.number, order, 1, 0), order);
  }

  // Getters
  public long _get_number() {
    return number;
  }

  public long _get_order() {
    return order;
  }  

  private static boolean is_prime(final long num) {
    if (num == 2 || num == 3) return true;
    if (num < 2 || num % 2 == 0) return false;
    if (num < 9) return true;
    if (num % 3 == 0) return false;

    long sqrt_num = (long) (Math.sqrt(num));
    long temp = 5;
    while (temp <= sqrt_num) {
      if (num % temp == 0) return false;
      if (num % (temp + 2) == 0) return false;
      temp += 6;
    }
    return true;
  }

  private class PrimeException extends Exception { 
    public PrimeException() {
        super("error: 'order' is not a prime number.");
    }
  }

}
