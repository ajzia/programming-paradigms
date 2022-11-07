from typing import Type
from galois_field import GaloisField
from copy import deepcopy
from random import randint

TEST_PRIME: int = 1234567891
TEST_FIELD = GaloisField(1234567891)

def constructor_test() -> None:
  field = deepcopy(TEST_FIELD)

  test_obj = field(1)

  print("\nCONSTRUCTOR TESTS:")
  print("   positive number test:")
  print(f"     {test_obj}.num == 1")
  assert test_obj.num == 1
  print(f"     {test_obj}.order == {TEST_PRIME}")
  assert test_obj.order == TEST_PRIME

  test_obj = field(-1)

  print(f"     {test_obj}.num == {-1 % TEST_PRIME}")
  assert test_obj.num == -1 % TEST_PRIME
  print(f"     {test_obj}.order == {TEST_PRIME}")
  assert test_obj.order == TEST_PRIME

  print("  TESTS PASSED!")

def add_test() -> None:
  field = deepcopy(TEST_FIELD)
  x: int = randint(-5 * 1234567891, 5 * 1234567891)
  y: int = randint(-5 * 1234567891, 5 * 1234567891)

  gf1 = field(x)
  gf2 = field(y)

  print("\nADD TESTS:")
  print("     + tests:")
  print(f"       {gf1} + {gf2} == f({x + y})")
  assert type(gf1 + gf2) is type(field(x + y))
  assert gf1 + gf2 == field(x + y)

  print(f"       {gf2} + {gf1} == f({y + x})")
  assert type(gf2 + gf1) is type(field(y + x))
  assert gf2 + gf1 == field(y + x)
  
  six = field(6)
  assert six.num == 6

  print("       f(6) + 3 = f(6) + f(3)\n")
  assert type(six + 3) is type(field(6 + 3))
  assert six + 3 == field(6 + 3)
  
  print("     += test:")
  print("       f(6) += 3 == f(6) + f(3)")
  six += 3
  assert six.num == field(6) + field(3)

  print("  TESTS PASSED!")

def sub_test() -> None:
  field = deepcopy(TEST_FIELD)
  x: int = randint(-5 * 1234567891, 5 * 1234567891)
  y: int = randint(-5 * 1234567891, 5 * 1234567891)

  gf1 = field(x)
  gf2 = field(y)

  print("\nSUB TESTS:")
  print("     - tests:")
  print(f"       {gf1} - {gf2} == f({x - y})")
  assert type(gf1 - gf2) is type(field(x - y))
  assert gf1 - gf2 == field(x - y)

  print(f"       {gf2} - {gf1} == f({y - x})")
  assert type(gf2 - gf1) is type(field(y - x))
  assert gf2 - gf1 == field(y - x)
  
  six = field(6)
  assert six.num == 6

  print("       f(6) - 3 = f(6) - f(3)\n")
  assert type(six - 3) is type(field(6 - 3))
  assert six - 3 == field(6 - 3)
  
  print("     -= test:")
  print("       f(6) -= 3 == f(6) - f(3)")
  six -= 3
  assert six.num == field(6) - field(3)

  print("  TESTS PASSED!")

def mul_test() -> None:
  field = deepcopy(TEST_FIELD)
  x: int = randint(-5 * 1234567891, 5 * 1234567891)
  y: int = randint(-5 * 1234567891, 5 * 1234567891)

  gf1 = field(x)
  gf2 = field(y)

  print("\nMUL TESTS:")
  print("     * tests:")
  print(f"       {gf1} * {gf2} == f({x * y})")
  assert type(gf1 * gf2) is type(field(x * y))
  assert gf1 * gf2 == field(x * y)

  print(f"       {gf2} * {gf1} == f({y * x})")
  assert type(gf2 * gf1) is type(field(y * x))
  assert gf2 * gf1 == field(y * x)
  
  six = field(6)
  assert six.num == 6

  print("       f(6) * 3 = f(6) * f(3)\n")
  assert type(six * 3) is type(field(6 * 3))
  assert six * 3 == field(6 * 3)

  print("     *= test:")
  print("       f(6) *= 3 == f(6) * f(3)")
  six *= 3
  assert six.num == field(6) * field(3)

  print("  TESTS PASSED!")

def div_test():
  field = deepcopy(TEST_FIELD)
  x = randint(-5 * 1234567891, 5 * 1234567891)
  y = randint(-5 * 1234567891, 5 * 1234567891)

  gf1 = field(x)
  gf2 = field(y)

  print("\nDIV TESTS:")
  print("     * tests:")
  print(f"       {gf1} / {gf2} == f({x * pow(y, -1, TEST_PRIME)})")
  assert type(gf1 / gf2) is type(field(x * pow(y, -1, TEST_PRIME)))
  assert gf1 / gf2 == field(x * pow(y, -1, TEST_PRIME))
  
  six = field(6)
  assert six.num == 6
  
  print("       f(6) / 3 = f(6) / f(3)")
  assert type(six / 3) is type(field(6) / field(3))
  assert six / 3 == field(6) / field(3)

  print("       3 / f(6) = f(3) / f(6)\n")
  assert type(3 / six) is type(field(3) / field(6))
  assert 3 / six == field(3) / field(6)

  six /= 3
  print("     /= tests:")
  print("       f(6) /= 3 = f(6) / f(3)")
  assert type(six) is type(field(6) / field(3))
  assert six == field(6) / field(3)

  print("  TESTS PASSED!")

def test_comparisons():
  field = deepcopy(TEST_FIELD)
  x = randint(-5 * 1234567891, 5 * 1234567891) % TEST_PRIME
  y = randint(-5 * 1234567891, 5 * 1234567891) % TEST_PRIME

  print("\nCOMPARISON TESTS:")
  print("     < tests:")
  print(f"       ({x} < {y}) == (f({x} < f({y}))\n")
  assert (x < y) == (field(x) < field(y))
  assert (field(0) < field(TEST_PRIME + 1))

  print("     > tests:")
  print(f"       ({x} > {y}) == (f({x} > f({y}))\n")
  assert (x > y) == (field(x) > field(y))
  assert (field(2) > field(TEST_PRIME + 1))

  print("     <= tests:")
  print(f"       ({x} <= {y}) == (f({x} <= f({y}))\n")
  assert (x <= y) == (field(x) <= field(y))
  assert (field(0) <= field(TEST_PRIME + 1))

  print("     => tests:")
  print(f"       ({x} => {y}) == (f({x} => f({y}))\n")
  assert (x >= y) == (field(x) >= field(y))
  assert (field(1) >= field(TEST_PRIME + 1))

  print("     == tests:")
  print(f"       ({x} == {y}) == (f({x} == f({y}))\n")
  assert (x == y) == (field(x) == field(y))
  assert (field(1) == field(TEST_PRIME + 1))

  print("     != tests:")
  print(f"       ({x} != {y}) == (f({x} != f({y}))")
  assert (x != y) == (field(x) != field(y))
  assert (field(1537) != field(TEST_PRIME + 1))

  print("  TESTS PASSED!")

def run_tests() -> None:
  constructor_test()
  add_test()
  sub_test()
  mul_test()
  div_test()
  test_comparisons()

if __name__ == "__main__":
  run_tests()
