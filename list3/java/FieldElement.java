public interface FieldElement<T> {
  T _add(T other);
  T _sub(T other);
  T _mul(T other);
  T _div(T other);
  T _neg();
  T _inv();
  T _one();
  T _zero();

  boolean _isZero();
  boolean _isOne();
  
  // Comparison operators
  boolean _eq(T other);
  boolean _neq(T other);
  boolean _lt(T other);
  boolean _gt(T other);
  boolean _le(T other);
  boolean _ge(T other);
}
