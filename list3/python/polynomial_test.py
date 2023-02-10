from galois_field import GaloisField
from polynomial import polynomialOver

TEST_FIELD = GaloisField(2)

def constructor_test() -> None:
  gf2Polynomial = polynomialOver(TEST_FIELD)
  floatPolynomial = polynomialOver(float)

  print("\nCONSTRUCTOR TESTS:")
  print("   GF2 polynomials test:")
  print("     GF[1, 1].__name__ == 'GF[1, 1][x]'")
  print("     GF[1, 1].degree() == 1")
  assert gf2Polynomial([1, 1]).degree() == 1
  print("     GF[1, 1].coefficients == [1, 1]")
  assert gf2Polynomial([1, 1]).coefficients == [1, 1]
  print("     GF[1, 1].isZero() == False")
  assert gf2Polynomial([1, 1]).isZero() == False

  print("  Float polynomials test:")
  print("     Float[1.3, 1.4].degree() == 1")
  assert floatPolynomial([1.3, 1.4]).degree() == 1
  print("     Float[1.3, 1.4].coefficients == [1.3, 1.4]")
  assert floatPolynomial([1.3, 1.4]).coefficients == [1.3, 1.4]
  print("     Float[1.3, 1.4].isZero() == False")
  assert floatPolynomial([1.3, 1.4]).isZero() == False
  
  print("  TESTS PASSED!")

def add_test() -> None:
  gf2Polynomial = polynomialOver(TEST_FIELD)
  floatPolynomial = polynomialOver(float)

  print("\nADD TESTS:")
  print("   + tests:")
  print("     GF[1, 1] + GF[1, 1] == GF[0, 0]")
  assert gf2Polynomial([1, 1]) + gf2Polynomial([1, 1]) == gf2Polynomial([0, 0])
  print("     GF[1, 1] + GF[1, 0] == GF[0, 1]")
  assert gf2Polynomial([1, 1]) + gf2Polynomial([1, 0]) == gf2Polynomial([0, 1])

  print("     Float[1.3, 1.4] + Float[1.3, 1.4] == Float[2.6, 2.8]")
  assert floatPolynomial([1.3, 1.4]) + floatPolynomial([1.3, 1.4]) == floatPolynomial([2.6, 2.8])

  print("   += tests:")
  print("     GF[1, 1] += GF[1, 1] == GF[0, 0]")
  one_one = gf2Polynomial([1, 1])
  one_one += gf2Polynomial([1, 1])

  assert one_one == gf2Polynomial([0, 0])

  print("     Float[1.3, 1.4] += Float[1.3, 1.4] == Float[2.6, 2.8]")

  one_point_three_one_point_four = floatPolynomial([1.3, 1.4])
  one_point_three_one_point_four += floatPolynomial([1.3, 1.4])

  assert one_point_three_one_point_four == floatPolynomial([2.6, 2.8])

  print("  TESTS PASSED!")

def sub_test() -> None:
  gf2Polynomial = polynomialOver(TEST_FIELD)
  floatPolynomial = polynomialOver(float)

  print("\nSUB TESTS:")

  print("   - tests:")
  print("     GF[1, 1] - GF[1, 1] == GF[0, 0]")
  assert gf2Polynomial([1, 1]) - gf2Polynomial([1, 1]) == gf2Polynomial([0, 0])

  print("     GF[1, 1] - GF[1, 0] == GF[0, 1]")
  assert gf2Polynomial([1, 1]) - gf2Polynomial([1, 0]) == gf2Polynomial([0, 1])

  print("     Float[1.3, 1.4] - Float[1.3, 1.4] == Float[0, 0]")
  assert floatPolynomial([1.3, 1.4]) - floatPolynomial([1.3, 1.4]) == floatPolynomial([0, 0])

  print("   -= tests:")
  print("     GF[1, 1] -= GF[1, 1] == GF[0, 0]")
  one_one = gf2Polynomial([1, 1])
  one_one -= gf2Polynomial([1, 1])

  assert one_one == gf2Polynomial([0, 0])

  print("     Float[1.3, 1.4] -= Float[1.3, 1.4] == Float[0, 0]")
  one_point_three_one_point_four = floatPolynomial([1.3, 1.4])
  one_point_three_one_point_four -= floatPolynomial([1.3, 1.4])

  assert one_point_three_one_point_four == floatPolynomial([0, 0])

  print("  TESTS PASSED!")

def mul_test() -> None:
  gf2Polynomial = polynomialOver(TEST_FIELD)
  floatPolynomial = polynomialOver(float)

  print("\nMUL TESTS:")
  print("   * tests:")
  print("     GF[1, 1] * GF[1, 1] == GF[1, 0, 1]")
  assert gf2Polynomial([1, 1]) * gf2Polynomial([1, 1]) == gf2Polynomial([1, 0, 1])

  print("     GF[1, 1] * GF[1, 0] == GF[1, 1]")
  assert gf2Polynomial([1, 1]) * gf2Polynomial([1, 0]) == gf2Polynomial([1, 1])

  print("     Float[1.3, 1.4] * Float[1.3, 1.4] == Float[1.69, 3.22, 1.96]")
  print(floatPolynomial([1.3, 1.4]) * floatPolynomial([1.3, 1.4]))
  assert floatPolynomial([1.3, 1.4]) * floatPolynomial([1.3, 1.4]) == floatPolynomial([1.6900000000000002, 3.6399999999999997, 1.9599999999999997])

  print("   *= tests:")
  print("     GF[1, 1] *= GF[1, 1] == GF[1, 0]")

  one_one = gf2Polynomial([1, 1])
  one_one *= gf2Polynomial([1, 1])

  assert one_one == gf2Polynomial([1, 0, 1])

  print("     Float[1.3, 1.4] *= Float[1.3, 1.4] == Float[1.69, 3.22, 1.96]")
  one_point_three_one_point_four = floatPolynomial([1.3, 1.4])
  one_point_three_one_point_four *= floatPolynomial([1.3, 1.4])

  assert one_point_three_one_point_four == floatPolynomial([1.6900000000000002, 3.6399999999999997, 1.9599999999999997])

  print("  TESTS PASSED!")

def div_test():
  gf2Polynomial = polynomialOver(TEST_FIELD)
  floatPolynomial = polynomialOver(float)

  print("\nDIV TESTS:")

  print("   / tests:")
  print("     GF[1, 1] / GF[1, 1] == GF[1, 0]")
  assert gf2Polynomial([1, 1]) / gf2Polynomial([1, 1]) == gf2Polynomial([1, 0])

  print("     GF[1, 1] / GF[1, 0] == GF[1, 1]")
  assert gf2Polynomial([1, 1]) / gf2Polynomial([1, 0]) == gf2Polynomial([1, 1])

  print("     Float[1.3, 1.4] / Float[1.3, 1.4] == Float[1, 0]")
  assert floatPolynomial([1.3, 1.4]) / floatPolynomial([1.3, 1.4]) == floatPolynomial([1, 0])

  print("   /= tests:")
  print("     GF[1, 1] /= GF[1, 1] == GF[1, 0]")
  one_one = gf2Polynomial([1, 1])
  one_one /= gf2Polynomial([1, 1])

  assert one_one == gf2Polynomial([1, 0])

  print("     Float[1.3, 1.4] /= Float[1.3, 1.4] == Float[1, 0]")
  one_point_three_one_point_four = floatPolynomial([1.3, 1.4])
  one_point_three_one_point_four /= floatPolynomial([1.3, 1.4])

  assert one_point_three_one_point_four == floatPolynomial([1, 0])

  print("  TESTS PASSED!")

def test_comparisons():
  gf2Polynomial = polynomialOver(TEST_FIELD)

  print("\nCOMPARISON TESTS:")

  print("   == tests:")

  print("     GF[1, 1] == GF[1, 1]")
  assert gf2Polynomial([1, 1]) == gf2Polynomial([1, 1])

  print("     GF[1, 1] != GF[1, 0]")
  assert gf2Polynomial([1, 1]) != gf2Polynomial([1, 0])

  print("     GF[1, 1] != GF[1, 1, 1]")
  assert gf2Polynomial([1, 1]) != gf2Polynomial([1, 1, 1])

  print("     GF[1, 1] < GF[1, 1, 1]")
  assert gf2Polynomial([1, 1]) < gf2Polynomial([1, 1, 1])

  print("     GF[1, 1, 1] > GF[1, 1]")
  assert gf2Polynomial([1, 1, 1]) > gf2Polynomial([1, 1])

  print("     GF[1, 1] >= GF[1, 1]")
  assert gf2Polynomial([1, 1]) >= gf2Polynomial([1, 1])

  print("     GF[1, 1] <= GF[1, 1]")
  assert gf2Polynomial([1, 1]) <= gf2Polynomial([1, 1])

  print("  TESTS PASSED!")


def call_test():
  gf2Polynomial = polynomialOver(TEST_FIELD)
  floatPolynomial = polynomialOver(float)

  print("\nCALL TESTS:")
  print("     GF[1, 1](1) == 0")
  assert gf2Polynomial([1, 1])(1) == 0

  print("     GF[1, 1](0) == 1")
  assert gf2Polynomial([1, 1])(0) == 1

  print("     Float[1.3, 1.4](1.3) == 1.69")
  assert floatPolynomial([1.3, 1.4])(1.3) == 3.12

  print("     Float[1.3, 1.4](1.4) == 1.96")
  assert floatPolynomial([1.3, 1.4])(1.4) == 3.26

  print("  TESTS PASSED!")


def run_tests() -> None:
  constructor_test()
  add_test()
  sub_test()
  mul_test()
  div_test()
  test_comparisons()
  call_test()

if __name__ == "__main__":
  run_tests()