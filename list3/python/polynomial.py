from itertools import zip_longest

def polynomialOver(field: float):
  class Polynomial:
    def __init__(self, coefficients):
      if isinstance(coefficients, Polynomial):
        self.coefficients = coefficients.coefficients
      elif hasattr(coefficients, '__iter__') or hasattr(coefficients, "iter"):
        self.coefficients = [field(x) for x in coefficients]
      else:
        self.coefficients = [field(coefficients)]

      if hasattr(self.coefficients, '__len__') or hasattr(self.coefficients, "len"):
        for i in range(len(self.coefficients) - 1, -1, -1):
          if self.coefficients[i] != field(0):
            break
          self.coefficients.pop(i)      
      
      self.__name__ = f"{field.__name__}[x]"

    def isZero(self):
      return self.coefficients == []

    # String representation
    def __repr__(self):
      if self.isZero():
        return "0"

      poly_repr = ""
      for i, a in enumerate(self.coefficients):
        if i == 0:
          poly_repr += f"{a}"
        elif i == 1:
          poly_repr += f" + {a}x"
        else:
          poly_repr += f" + {a}x^{i}"
      
      return f"{self.__name__} = " + poly_repr

    def __str__(self):
      return repr(self)

    # Polynomial degree methods (len, abs, degree)
    def __len__(self):
      return len(self.coefficients)
    def __abs__(self):
      return len(self.coefficients)
    def degree(self):
      return abs(self) - 1

    # Make Polynomial iterable
    def __iter__(self):
      return iter(self.coefficients)
    def iter(self):
      return self.__iter__()

    # Arithmetic
    @typecast
    def __add__(self, other):
      new_coeffs = [sum(x) for x in zip_longest(self, other, fillvalue=field(0))]
      return Polynomial(new_coeffs)

    def __neg__(self):
      return Polynomial([-a for a in self])

    @typecast
    def __sub__(self, other):
      return self + (-other)

    @typecast
    def __mul__(self, other):
      if self.isZero() or other.isZero():
        return Polynomial(0)
      new_coeffs = [field(0)] * (len(self) + len(other) - 1)
      for i, a in enumerate(self):
        for j, b in enumerate(other):
          new_coeffs[i + j] += a * b
      return Polynomial(new_coeffs)

    @typecast
    def __divmod__(self, div):
      if div.isZero():
        raise ZeroDivisionError("Division by zero")
      if self.degree() < div.degree():
        return Polynomial([]), self
      
      quot, rem = Polynomial([]), self
      div_degree = div.degree()
      div_tail = div.coefficients[-1]

      while rem.degree() >= div_degree:
        degree = rem.degree() - div_degree
        term = [field(0)] * degree
        coeff = [rem.coefficients[-1] / div_tail]
        term = Polynomial(term + coeff)
        quot += term
        rem -= term * div

      return quot, rem

    @typecast
    def __truediv__(self, div):
      quot, _ = divmod(self, div)
      return quot
    
    @typecast
    def __div__(self, div):
      quot, _ = divmod(self, div)
      return quot

    @typecast
    def __mod__(self, div):
      _, rem = divmod(self, div)
      return rem

    # Get polynomial value
    def __call__(self, x):
      return sum([a * (x ** i) for i, a in enumerate(self)])

    # Comparison
    @typecast
    def __eq__(self, other):
      return self.coefficients == other.coefficients

    @typecast
    def __ne__(self, other):
      return self.coefficients != other.coefficients

    @typecast
    def __lt__(self, other):
      if (self.degree() < other.degree()):
        return True
      for i in range(other.degree(), -1, -1):
        if self.coefficients[i] < other.coefficients[i]:
          return True
        elif self.coefficients[i] > other.coefficients[i]:
          return False
      return False

    @typecast
    def __gt__(self, other):
      if (self.degree() > other.degree()):
        return True
      for i in range(other.degree(), -1, -1):
        if self.coefficients[i] > other.coefficients[i]:
          return True
        elif self.coefficients[i] < other.coefficients[i]:
          return False
      return False
  
    @typecast
    def __le__(self, other):
      return self < other or self == other

    @typecast
    def __ge__(self, other):
      return self > other or self == other

    # Get polynomial coefficient
    def __getitem__(self, i):
      if i < 0:
        i += len(self)
      if i < 0 or i >= len(self):
        raise IndexError(f"Index {i} out of range")
      return self.coefficients[i]

    # Set polynomial coefficient
    def __setitem__(self, i, val):
      if i < 0:
        i += len(self)
      if i < 0 or i >= len(self):
        raise IndexError(f"Index {i} out of range")
      self.coefficients[i] = val

    # Right-side arithmetic

    def __radd__(self, other):
      return self + other
    
    def __rsub__(self, other):
      return -self + other

    def __rmul__(self, other):
      return self * other

    def __rdivmod__(self, other):
      return divmod(other, self)

    def __rtruediv__(self, other):
      return other / self

    def __rdiv__(self, other):
      return other / self

  return Polynomial


def typecast(f):
  def __cast(self, other):
    if type(self) is not type(other):
      try:
        other = self.__class__(other) # FieldElement(other)
      except Exception as e:
        raise TypeError(
          f"Couldn't cast {other} of type {type(other).__name__} to type " \
          f"{type(self).__name__} in func={f.__name__}.\n" \
          f"Reason: {e}"
        )
    return f(self, other)
  return __cast


def is_prime(num):
  if num == 2 or num == 3: return True
  if num < 2 or num % 2 == 0: return False
  if num < 9: return True
  if num % 3 == 0: return False
  sqrt_num = int(num ** 0.5) # truncated sqrt
  cand = 5
  while cand <= sqrt_num:
    if num % cand == 0: return False
    if num % (cand+2) == 0: return False
    cand += 6
  return True
