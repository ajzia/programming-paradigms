public class RealNumber implements FieldElement<RealNumber> {
  private double num;

  public RealNumber(final double number) {
    this.num = number;
  }

  public double _get_number() {
    return this.num;
  }

  public RealNumber _add(RealNumber other) {
    return new RealNumber(this.num + other._get_number());
  }

  public RealNumber _sub(RealNumber other) {
    return new RealNumber(this.num - other._get_number());
  }

  public RealNumber _mul(RealNumber other) {
    return new RealNumber(this.num * other._get_number());
  }

  public RealNumber _div(RealNumber other) {
    return new RealNumber(this.num / other._get_number());
  }

  public RealNumber _neg() {
    return new RealNumber(-this.num);
  }

  public RealNumber _inv() {
    return new RealNumber(1 / this.num);
  }

  public RealNumber _one() {
    return new RealNumber(1);
  }

  public RealNumber _zero() {
    return new RealNumber(0);
  }

  public boolean _isZero() {
    return (this.num == 0);
  }

  public boolean _isOne() {
    return (this.num == 1);  
  }

  public boolean _eq(RealNumber other) {
    return (this.num == other._get_number());
  }

  public boolean _neq(RealNumber other) {
    return (this.num != other._get_number());
  }

  public boolean _lt(RealNumber other) {
    return (this.num < other._get_number());
  }

  public boolean _gt(RealNumber other) {
    return (this.num > other._get_number());
  }

  public boolean _le(RealNumber other) {
    return (this.num <= other._get_number());
  }

  public boolean _ge(RealNumber other) {
    return (this.num >= other._get_number());
  }
  
  public String toString() {
    return Double.toString(this.num);
  }
}