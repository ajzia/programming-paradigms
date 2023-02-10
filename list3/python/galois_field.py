def GaloisField(order: int):
  if not (isinstance(order, int)):
    raise ValueError(f"Order={order} is not an integer.")
  if not is_prime(order):
    raise ValueError(f"Order={order} is not prime.")

  class FieldElement():
    # Constructor
    def __init__(self, num: int, /):
      if isinstance(num, FieldElement):
        self.num = num.num
      else:
        self.num = num % order

    # Printing
    def __str__(self):
      return f"GF<{order}>({self.num})"

    # Arithmetic operators
    def __neg__(self):
      return FieldElement(-self.num)

    @typecast
    def __add__(self, other):
      return FieldElement(self.num + other.num)  

    @typecast
    def __sub__(self, other):
      return FieldElement(self.num - other.num)  

    @typecast
    def __mul__(self, other):
      return FieldElement(self.num * other.num)

    @typecast
    def __pow__(self, other):
      return FieldElement(self.num ** other.num)

    @typecast
    def __truediv__(self, other):
      return self * other.mod_inverse()

    @typecast
    def __div__(self, other):
      return self * other.mod_inverse()

    @typecast
    def __divmod__(self, other):
      (quot, remainder) = divmod(self.num, other.num)
      return (FieldElement(quot), FieldElement(remainder))

    def mod_inverse(self):
      return FieldElement(pow(self.num, -1, self.order))
      
    # Comparison operators
    @typecast
    def __eq__(self, other):
      return self.num == other.num

    @typecast
    def __lt__(self, other):
      return self.num < other.num

    @typecast
    def __le__(self, other):
      return self.__lt__(other) or self.__eq__(other)

    @typecast
    def __gt__(self, other):
      return self.num > other.num

    @typecast
    def __ge__(self, other):
      return self.__gt__(other) or self.__eq__(other)

    # Right-side arithmetic operators
    def __radd__(self, other): 
      return self + other

    def __rsub__(self, other): 
      return -self + other
    
    def __rmul__(self, other): 
      return self * other
    
    def __rtruediv__(self, other): 
      return self.mod_inverse() * other
    
    def __rdiv__(self, other): 
      return self.__rtruediv__(other)

  FieldElement.order = order
  return FieldElement

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
