import java.util.ArrayList;

public class Polynomial<T extends FieldElement<T>> {

  private ArrayList<T> coefficients;
  private int degree;

  private void remove_trailing_zeros() {
    while (this.coefficients.size() > 1 && this.coefficients.get(this.coefficients.size() - 1)._isZero()) {
      this.coefficients.remove(this.coefficients.size() - 1);
    }
    this.degree = this.coefficients.size() - 1;
  }

  public Polynomial(final T[] coefficients) {
    this.coefficients = new ArrayList<T>();
    for (int i = 0; i < coefficients.length; i++) {
      this.coefficients.add(coefficients[i]);
    }
    this.remove_trailing_zeros();
  }

  public Polynomial(final ArrayList<T> coeffs) {
    this.coefficients = coeffs;
    this.remove_trailing_zeros();
  }

  public Polynomial(final Polynomial<T> p) {
    this.coefficients = new ArrayList<T>();
    for (int i = 0; i < p.coefficients.size(); i++) {
      this.coefficients.add(p.coefficients.get(i));
    }

    this.degree = p.degree;
    this.remove_trailing_zeros();
  }

  public Polynomial(final T coeff) {
    this.coefficients = new ArrayList<T>();
    this.coefficients.add(coeff);
    this.degree = 0;
  }

  public int get_degree() {
    return this.degree;
  }

  public T get_coeff(final int i) {
    return this.coefficients.get(i);
  }

  public Polynomial<T> _add(final Polynomial<T> p) {
    ArrayList<T> result = new ArrayList<T>();
    int new_size = this.degree + p.degree + 1;

    for (int i = 0; i < new_size; i++) {
      if (i <= this.degree) {
        if (i <= p.degree) {
          result.add(this.coefficients.get(i)._add(p.coefficients.get(i)));
        } else {
          result.add(this.coefficients.get(i));
        }
      } else if (i <= p.degree) {
        result.add(p.coefficients.get(i));
      }
    }

    return new Polynomial<T>(result);
  }

  public Polynomial<T> sub(final Polynomial<T> p) {
    ArrayList<T> result = new ArrayList<T>();
    int new_size = this.degree + p.degree + 1;

    for (int i = 0; i < new_size; i++) {
      if (i <= this.degree) {
        if (i <= p.degree) {
          result.add(this.coefficients.get(i)._sub(p.coefficients.get(i)));
        } else {
          result.add(this.coefficients.get(i));
        }
      } else if (i <= p.degree) {
        result.add(p.coefficients.get(i)._neg());
      }
    }

    return new Polynomial<T>(result);
  }

  public Polynomial<T> mul(final Polynomial<T> p) {
    ArrayList<T> result = new ArrayList<T>();
    for (int i = 0; i <= this.degree + p.degree; i++) {
      result.add(this.coefficients.get(0)._zero());
    }

    for (int i = 0; i <= this.degree; i++) {
      for (int j = 0; j <= p.degree; j++) {
        result.set(i + j, result.get(i + j)._add(this.coefficients.get(i)._mul(p.coefficients.get(j))));
      }
    }
    return new Polynomial<T>(result);
  }

  public Polynomial<T> mul(final T coeff) {
    ArrayList<T> result = new ArrayList<T>();
    for (int i = 0; i <= this.degree; i++) {
      result.add(this.coefficients.get(i)._mul(coeff));
    }

    return new Polynomial<T>(result);
  }

  public Polynomial<T>[] divmod(final Polynomial<T> p) {
    Polynomial<T>[] result = new Polynomial[2];
    Polynomial<T> quotient = new Polynomial<T>(this.coefficients.get(0)._zero());
    Polynomial<T> remainder = new Polynomial<T>(this);

    while (remainder.degree >= p.degree) {
      T factor = remainder.coefficients.get(remainder.degree)._div(p.coefficients.get(p.degree));
      Polynomial<T> term = new Polynomial<T>(factor);

      for (int i = 0; i < remainder.degree - p.degree; i++) {
        term.coefficients.add(0, term.coefficients.get(0)._zero());
      }
      
      quotient = quotient._add(term);
      remainder = remainder.sub(p.mul(term));
    }

    result[0] = quotient;
    result[1] = remainder;
    return result;
  }

  public Polynomial<T> div(final Polynomial<T> p) {
    return this.divmod(p)[0];
  }

  public Polynomial<T> mod(final Polynomial<T> p) {
    return this.divmod(p)[1];
  }

  public boolean eq(final Polynomial<T> polynomial) {
    if (this.degree != polynomial.degree) {
      return false;
    }

    for (int i = 0; i <= this.degree; i++) {
      if (this.coefficients.get(i)._neq(polynomial.coefficients.get(i))) {
        return false;
      }
    }

    return true;
  }

  public boolean neq(final Polynomial<T> polynomial) {
    return !this.eq(polynomial);
  }

  public boolean lt(final Polynomial<T> polynomial) {
    if (this.degree < polynomial.degree) {
      return true;
    }
    if (this.degree > polynomial.degree) {
      return false;
    }
    for (int i = this.degree; i >= 0; i--) {
      if (this.coefficients.get(i)._lt(polynomial.coefficients.get(i))) {
        return true;
      }

      if (this.coefficients.get(i)._gt(polynomial.coefficients.get(i))) {
        return false;
      }
    }
    return false;
  }

  public boolean gt(final Polynomial<T> polynomial) {
    if (this.degree > polynomial.degree) {
      return true;
    }

    if (this.degree < polynomial.degree) {
      return false;
    }

    for (int i = this.degree; i >= 0; i--) {
      if (this.coefficients.get(i)._gt(polynomial.coefficients.get(i))) {
        return true;
      }

      if (this.coefficients.get(i)._lt(polynomial.coefficients.get(i))) {
        return false;
      }
    }

    return false;
  }

  public boolean le(final Polynomial<T> polynomial) {
    return this.lt(polynomial) || this.eq(polynomial);
  }

  public boolean ge(final Polynomial<T> polynomial) {
    return this.gt(polynomial) || this.eq(polynomial);
  }

  public T value(final T x) {
    T result = this.coefficients.get(0);
    T power = x;
    
    for (int i = 1; i <= this.degree; i++) {
      result = result._add(this.coefficients.get(i)._mul(power));
      power = power._mul(x);
    }
    return result;
  }

  public String toString() {
    String result = "";
    for (int i = 0; i < this.degree; i++) {
      if (this.coefficients.get(i)._isZero())
        continue;

      if (i == 0) {
        result += this.coefficients.get(i).toString();
      } else {
        result += this.coefficients.get(i) + "x^" + i;
      }

      result += " + ";
    }

    result += this.coefficients.get(this.degree).toString();
    return result;
  }

  public boolean equals(Object other) {
    if (other == null || !(other instanceof Polynomial)) {
      return false;
    }

    if (other == this) {
      return true;
    }

    Polynomial<T> other_polynomial = (Polynomial<T>) other;
    if (this.degree != other_polynomial.degree) {
      return false;
    }

    for (int i = 0; i <= this.degree; i++) {
      if (this.coefficients.get(i)._neq(other_polynomial.coefficients.get(i))) {
        return false;
      }
    }

    return true;
  }
}
