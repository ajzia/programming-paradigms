/*
  g++ polynomial_main.cpp galois_field.cpp polynomial.cpp && ./a.out
*/

#include <iostream>
#include <vector>
#include "galois_field.cpp"
#include <cassert>
#include "polynomial.cpp"

using namespace std;

static const uint64_t TEST_PRIME = 2;

static void constructor_test(void) {
  cout << "CONSTRUCTOR TESTS:\n";

  vector<double> coeffs = {1.1, 2.2, 3.3, 4.5, 5.5};
  Polynomial<double> p1(coeffs);
  cout << "     Polynomial<double>({1.1, 2.2, 3.3, 4.5, 5.5}) degree == 4\n";
  assert(p1.get_degree() == 4);

  Polynomial<double> p2(coeffs[0]);
  cout << "     Polynomial<double>(1.1) degree == 0\n";
  assert(p2.get_degree() == 0);

  Polynomial<double> p3(p1);
  cout << "     Polynomial<double>(Polynomial<double>) degree == 4\n";
  assert(p3.get_degree() == 4);

  vector<double> coeffs2 = {0.0, 3.3, 0.0, 0.0};
  Polynomial<double> p4(coeffs2);
  cout << "     Polynomial<double>({0.0, 3.3, 0.0, 0.0}) degree == 1\n";
  assert(p4.get_degree() == 1);

  GaloisField<TEST_PRIME> gf2(0);
  vector<GaloisField<TEST_PRIME>> gf_coeffs = {gf2(1), gf2(3), gf2(4), gf2(5)};
  Polynomial<GaloisField<TEST_PRIME>> p_gf(gf_coeffs);
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) degree == 3" << endl;
  assert(p_gf.get_degree() == 3);

  Polynomial<GaloisField<TEST_PRIME>> p_gf2(gf2(1));
  cout << "     Polynomial<GaloisField<TEST_PRIME>>(gf2(1)) degree == 0" << endl;
  assert(p_gf2.get_degree() == 0);

  Polynomial<GaloisField<TEST_PRIME>> p_gf3(p_gf);
  cout << "     Polynomial<GaloisField<TEST_PRIME>>(Polynomial<GaloisField<TEST_PRIME>>) degree == 3" << endl;
  assert(p_gf3.get_degree() == 3);

  vector<GaloisField<TEST_PRIME>> gf_coeffs2 = {gf2(0), gf2(3), gf2(4), gf2(2)};
  Polynomial<GaloisField<TEST_PRIME>> p_gf4(gf_coeffs2);
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(0), gf2(3), gf2(4), gf2(2)}) degree == 1" << endl;
  assert(p_gf4.get_degree() == 1);

  cout << "   TESTS PASSED!\n";
}

static void add_test(void) {
  cout << "\nADD TESTS:\n";

  cout << "   + test:\n";
  vector<double> coeffs = {1.1, 2.2, 3.3};
  Polynomial<double> p1(coeffs), p2(coeffs);
  Polynomial<double> p3 = p1 + vector<double>{3.0, 4.5, 0.0, 0.0, 5.2};
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) + {3.0, 4.5, 0.0, 0.0, 5.2} == {4.1, 6.7, 3.3, 0.0, 5.2})\n";
  assert(p3.get_degree() == 4);
  assert(p3 == vector<double>({4.1, 6.7, 3.3, 0.0, 5.2}));

  p3 = p1 + 2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) + 2 == {3.1, 2.2, 3.3})\n";
  assert(p3.get_degree() == 2);
  assert(p3 == vector<double>({3.1, 2.2, 3.3}));

  vector<double> coeffs2 = {1, 1, 0, 4};
  vector<double> result2 = {2.1, 3.2, 3.3, 4};
  p3 = p1 + coeffs2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) + {1, 1, 0, 4} == {2.1, 3.2, 3.3, 4})\n";
  assert(p3.get_degree() == 3);
  assert(p3 == result2);

  vector<double> result = {2.2, 4.4, 6.6};
  p3 = p1 + p2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) + Polynomial<double>({1.1, 2.2, 3.3}) == {2.2, 4.4, 6.6})\n";
  assert(p3.get_degree() == 2);
  assert(p3 == result);

  // Polynomial gf2 + polynomial gf2
  GaloisField<TEST_PRIME> gf2(0);
  vector<GaloisField<TEST_PRIME>> gf_coeffs1 = {gf2(1), gf2(3), gf2(4), gf2(5)}, gf_coeffs2 = {gf2(0), gf2(3), gf2(4), gf2(2)};
  vector<GaloisField<TEST_PRIME>> gf_result = {gf2(0)};
  Polynomial<GaloisField<TEST_PRIME>> p_gf1(gf_coeffs1), p_gf2(gf_coeffs2);
  Polynomial<GaloisField<TEST_PRIME>> p_gf3 = p_gf1 + gf_coeffs1;
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) + {gf2(1), gf2(3), gf2(4), gf2(5)} == {gf2(0)}" << endl;
  assert(p_gf3.get_degree() == 0);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1 + gf2(1);
  gf_result = {gf2(0), gf2(1), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) + gf2(1) == {gf2(0), gf2(1), gf2(0), gf2(1)}" << endl;
  assert(p_gf3.get_degree() == 3);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1 + vector<GaloisField<TEST_PRIME>>{gf2(1), gf2(3), gf2(4), gf2(5), gf2(1)};
  gf_result = {gf2(0), gf2(0), gf2(0), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) + {gf2(1), gf2(3), gf2(4), gf2(5), gf2(1)} == {gf2(0), gf2(0), gf2(0), gf2(0), gf2(1)}" << endl;
  assert(p_gf3.get_degree() == 4);
  assert(p_gf3 == gf_result);

  gf_result = {gf2(1), gf2(0), gf2(0), gf2(1)};
  p_gf3 = p_gf1 + p_gf2;
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) + Polynomial<GaloisField<TEST_PRIME>>({gf2(0), gf2(3), gf2(4), gf2(2)}) == {gf2(1), gf2(0), gf2(0), gf2(1)}" << endl;
  assert(p_gf3.get_degree() == 3);
  assert(p_gf3 == gf_result);


  cout << "   += test:\n";
  p3 = Polynomial<double>(coeffs);
  p3 += vector<double>{3, 4, 0, 0, 5};
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) += {3, 4, 0, 0, 5} == {4.1, 6.2, 3.3, 0.0, 5})\n";
  assert(p3.get_degree() == 4);
  assert(p3 == vector<double>({4.1, 6.2, 3.3, 0, 5}));

  p3 = Polynomial<double>(coeffs);
  p3 += 2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) += 2 == {3.1, 2.2, 3.3})\n";
  assert(p3.get_degree() == 2);
  assert(p3 == vector<double>({3.1, 2.2, 3.3}));

  p3 = Polynomial<double>(coeffs);
  p3 += coeffs2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) += {1, 1, 0, 4} == {2.1, 3.2, 3.3, 4})\n";
  assert(p3.get_degree() == 3);
  assert(p3 == result2);

  p3 = Polynomial<double>(coeffs);
  p3 += p2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) += Polynomial<double>({1.1, 2.2, 3.3}) == {2.2, 4.4, 6.6})\n";
  assert(p3.get_degree() == 2);
  assert(p3 == result);

  p_gf3 = Polynomial<GaloisField<TEST_PRIME>>(gf_coeffs1);
  p_gf3 += gf_coeffs1;
  gf_result = {gf2(0)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) += {gf2(1), gf2(3), gf2(4), gf2(5)} == {gf2(0)}" << endl;
  assert(p_gf3.get_degree() == 0);
  assert(p_gf3 == gf_result);

  p_gf3 = Polynomial<GaloisField<TEST_PRIME>>(gf_coeffs1);
  p_gf3 += gf2(1);
  gf_result = {gf2(0), gf2(3), gf2(4), gf2(5)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) += gf2(1) == {gf2(0), gf2(3), gf2(4), gf2(5)}" << endl;
  assert(p_gf3.get_degree() == 3);
  assert(p_gf3 == gf_result);

  p_gf3 = Polynomial<GaloisField<TEST_PRIME>>(gf_coeffs1);
  p_gf3 += vector<GaloisField<TEST_PRIME>>{gf2(1), gf2(3), gf2(4), gf2(5), gf2(1)};
  gf_result = {gf2(0), gf2(0), gf2(0), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) + {gf2(1), gf2(3), gf2(4), gf2(5), gf2(1)} == {gf2(0), gf2(0), gf2(0), gf2(0), gf2(1)}" << endl;
  assert(p_gf3.get_degree() == 4);
  assert(p_gf3 == gf_result);

  p_gf3 = Polynomial<GaloisField<TEST_PRIME>>(gf_coeffs1);
  p_gf3 += p_gf1;
  gf_result = {gf2(0)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) += Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) == {gf2(0)}" << endl;
  assert(p_gf3.get_degree() == 0);
  assert(p_gf3 == gf_result);

  cout << "   TESTS PASSED!\n";
}

static void sub_test(void) {
  cout << "\nSUB TESTS:\n";

  cout << "   - test:\n";
  vector<double> coeffs = {1.1, 2.2, 3.3};
  Polynomial<double> p1(coeffs), p2(coeffs);
  Polynomial<double> p3 = p1 - vector<double>{3.0, 4.5, 0.0, 0.0, 5.2};
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) - {3.0, 4.5, 0.0, 0.0, 5.2} == {-1.9, -2.3, 3.3, 0.0, -5.2})\n";
  assert(p3.get_degree() == 4);
  assert(p3 == vector<double>({-1.9, -2.3, 3.3, 0.0, -5.2}));

  p3 = p1 - 0.1;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) - 0.1 == {1, 2.2, 3.3})\n";
  assert(p3.get_degree() == 2);
  assert(p3 == vector<double>({1, 2.2, 3.3}));

  vector<double> coeffs2 = {1, 1, 0, 4};
  vector<double> result = {0.1, 1.2, 3.3, -4};
  p3 = p1 - coeffs2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) - {1, 1, 0, 4} == {0.1, 1.2, 3.3, -4})\n";
  assert(p3.get_degree() == 3);

  for (int i = 0; i < p3.get_degree(); i++)
    assert(abs(p3[i] - result[i]) < 0.01);

  p3 = Polynomial<double>(coeffs);
  result = {0, 0, 0};
  p3 = p1 - p2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) - Polynomial<double>({1.1, 2.2, 3.3}) == {0, 0, 0})\n";
  assert(p3.get_degree() == 0);
  for (int i = 0; i < p3.get_degree(); i++)
    assert(abs(p3[i] - result[i]) < 0.01);

  GaloisField<TEST_PRIME> gf2(0);
  vector<GaloisField<TEST_PRIME>> gf_coeffs1 = {gf2(1), gf2(3), gf2(4), gf2(5)}, gf_coeffs2 = {gf2(0), gf2(3), gf2(4), gf2(2)};
  vector<GaloisField<TEST_PRIME>> gf_result = {gf2(0)};
  Polynomial<GaloisField<TEST_PRIME>> p_gf1(gf_coeffs1), p_gf2(gf_coeffs2);
  Polynomial<GaloisField<TEST_PRIME>> p_gf3 = p_gf1 - vector<GaloisField<TEST_PRIME>>{gf2(1), gf2(3), gf2(4), gf2(5)};

  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) - {gf2(1), gf2(3), gf2(4), gf2(5), gf2(0)} == {gf2(0)}" << endl;
  assert(p_gf3.get_degree() == 0);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1 - gf2(1);
  gf_result = {gf2(0), gf2(3), gf2(4), gf2(5)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) - gf2(1) == {gf2(0), gf2(3), gf2(4), gf2(5)}" << endl;
  assert(p_gf3.get_degree() == 3);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1 - vector<GaloisField<TEST_PRIME>>{gf2(1), gf2(1), gf2(0), gf2(1), gf2(1)};
  gf_result = {gf2(0), gf2(0), gf2(0), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) - {gf2(1), gf2(1), gf2(0), gf2(1), gf2(1)} == {gf2(0), gf2(0), gf2(0), gf2(0), gf2(1)}" << endl;
  assert(p_gf3.get_degree() == 4);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1 - p_gf2;
  gf_result = {gf2(1), gf2(0), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) - Polynomial<GaloisField<TEST_PRIME>>({gf2(0), gf2(3), gf2(4), gf2(2)}) == {gf2(1), gf2(0), gf2(0), gf2(1)}" << endl;
  assert(p_gf3.get_degree() == 3);
  assert(p_gf3 == gf_result);

  cout << "   -= test:\n";
  p3 = Polynomial<double>(coeffs);
  result = {-1.9, -1.8, 3.3, 0.0, -5};
  p3 -= vector<double>{3, 4, 0, 0, 5};
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) -= {3, 4, 0, 0, 5} == {-1.9, -1.8, 3.3, 0.0, -5})\n";
  assert(p3.get_degree() == 4);
  for (int i = 0; i < p3.get_degree(); i++)
    assert(abs(p3[i] - result[i]) < 0.01);

  p3 = Polynomial<double>(coeffs);
  result = {1, 2.2, 3.3};
  p3 -= 0.1;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) -= 0.1 == {1, 2.2, 3.3})\n";
  assert(p3.get_degree() == 2);
  for (int i = 0; i < p3.get_degree(); i++)
    assert(abs(p3[i] - result[i]) < 0.01);

  p3 = Polynomial<double>(coeffs);
  result = {0.1, 1.2, 3.3, -4};
  p3 -= coeffs2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) -= {1, 1, 0, 4} == {0.1, 1.2, 3.3, -4})\n";
  assert(p3.get_degree() == 3);
  for (int i = 0; i < p3.get_degree(); i++)
    assert(abs(p3[i] - result[i]) < 0.01);

  p3 = Polynomial<double>(coeffs);
  result = {0, 0, 0};
  p3 -= p2;
  cout << "     Polynomial<double>({1.1, 2.2, 3.3}) -= Polynomial<double>({1.1, 2.2, 3.3}) == {0, 0, 0})\n";
  assert(p3.get_degree() == 0);
  for (int i = 0; i < p3.get_degree(); i++)
    assert(abs(p3[i] - result[i]) < 0.01);

  p_gf3 = p_gf1;
  p_gf3 -= vector<GaloisField<TEST_PRIME>>{gf2(1), gf2(3), gf2(4), gf2(5)};
  gf_result = {gf2(0)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) -= {gf2(1), gf2(3), gf2(4), gf2(5)} == {gf2(0)}" << endl;
  assert(p_gf3.get_degree() == 0);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1;
  p_gf3 -= gf2(1);
  gf_result = {gf2(0), gf2(3), gf2(4), gf2(5)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) -= gf2(1) == {gf2(0), gf2(3), gf2(4), gf2(5)}" << endl;
  assert(p_gf3.get_degree() == 3);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1;
  p_gf3 -= p_gf2;
  gf_result = {gf2(1), gf2(0), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(3), gf2(4), gf2(5)}) -= Polynomial<GaloisField<TEST_PRIME>>({gf2(0), gf2(3), gf2(4), gf2(2)}) == {gf2(1), gf2(0), gf2(0), gf2(1)}" << endl;
  assert(p_gf3.get_degree() == 3);
  assert(p_gf3 == gf_result);

  cout << "   TESTS PASSED!\n";
}

static void mul_test(void) {
  cout << "\n MUL TESTS:\n";

  cout << "   * test:\n";
  vector<double> coeffs = {1, 2, 3};
  Polynomial<double> p1 = Polynomial<double>(coeffs);
  Polynomial<double> p2 = Polynomial<double>(coeffs);
  Polynomial<double> p3 = p1 * p2;
  vector<double> result = {1, 4, 10, 12, 9};
  cout << "     Polynomial<double>({1, 2, 3}) * Polynomial<double>({1.1, 2.2, 3.3}) == Polynomial<double>({1, 4, 10, 12, 9})\n";
  assert(p3.get_degree() == 4);
  assert(p3 == result);

  p3 = p1 * 2;
  result = {2, 4, 6};
  cout << "     Polynomial<double>({1, 2, 3}) * 2 == Polynomial<double>({2, 4, 6})\n";
  assert(p3.get_degree() == 2);
  assert(p3 == result);

  p3 = p1 * vector<double>{1, 2, 3, 4};
  result = {1, 4, 10, 16, 17, 12};
  cout << "     Polynomial<double>({1, 2, 3}) * {1, 2, 3, 4} == Polynomial<double>({1, 4, 10, 16, 17, 12})\n";
  assert(p3.get_degree() == 5);
  assert(p3 == result);

  GaloisField<TEST_PRIME> gf2(0);
  vector<GaloisField<TEST_PRIME>> gf_coeffs = {gf2(1), gf2(2), gf2(3)};
  Polynomial<GaloisField<TEST_PRIME>> p_gf1(gf_coeffs), p_gf2(gf_coeffs);
  Polynomial<GaloisField<TEST_PRIME>> p_gf3 = p_gf1 * p_gf2;
  vector<GaloisField<TEST_PRIME>> gf_result = {gf2(1), gf2(0), gf2(0), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(2), gf2(3)}) * Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(2), gf2(3)}) == {gf2(1), gf2(0), gf2(0), gf2(0), gf2(1)}" << endl;
  assert(p_gf3.get_degree() == 4);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1 * gf2(1);
  gf_result = {gf2(1), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(2), gf2(3)}) * gf2(2) == {gf2(1), gf2(0), gf2(1)};" << endl;
  assert(p_gf3.get_degree() == 2);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1 * vector<GaloisField<TEST_PRIME>>{gf2(1), gf2(0)};
  gf_result = {gf2(1), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(2), gf2(3)}) * {gf2(1), gf2(0)} == {gf2(1), gf2(0), gf2(1)};" << endl;
  assert(p_gf3.get_degree() == 2);
  assert(p_gf3 == gf_result);

  cout << "   * test:\n";
  p3 = p1;
  p3 *= p2;
  result = {1, 4, 10, 12, 9};
  cout << "     Polynomial<double>({1, 2, 3}) *= Polynomial<double>({1.1, 2.2, 3.3}) == Polynomial<double>({1, 4, 10, 12, 9})\n";
  assert(p3.get_degree() == 4);
  assert(p3 == result);

  p3 = p1;
  p3 *= 2;
  result = {2, 4, 6};
  cout << "     Polynomial<double>({1, 2, 3}) *= 2 == Polynomial<double>({2, 4, 6})\n";
  assert(p3.get_degree() == 2);
  assert(p3 == result);

  p3 = p1;
  p3 *= vector<double>{1, 2, 3, 4};
  result = {1, 4, 10, 16, 17, 12};
  cout << "     Polynomial<double>({1, 2, 3}) *= {1, 2, 3, 4} == Polynomial<double>({1, 4, 10, 16, 17, 12})\n";
  assert(p3.get_degree() == 5);
  assert(p3 == result);

  p_gf3 = p_gf1;
  p_gf3 *= p_gf2;
  cout << p_gf3 << endl;
  gf_result = {gf2(1), gf2(0), gf2(0), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(2), gf2(3)}) *= Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(2), gf2(3)}) == {gf2(1), gf2(0), gf2(0), gf2(0), gf2(1)}" << endl;
  assert(p_gf3.get_degree() == 4);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1;
  p_gf3 *= gf2(1);
  cout << p_gf3 << endl;
  gf_result = {gf2(1), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(2), gf2(3)}) *= gf2(2) == {gf2(1), gf2(0), gf2(1)};" << endl;
  assert(p_gf3.get_degree() == 2);
  assert(p_gf3 == gf_result);

  p_gf3 = p_gf1;
  p_gf3 *= vector<GaloisField<TEST_PRIME>>{gf2(1), gf2(0)};
  cout << p_gf3 << endl;
  gf_result = {gf2(1), gf2(0), gf2(1)};
  cout << "     Polynomial<GaloisField<TEST_PRIME>>({gf2(1), gf2(2), gf2(3)}) *= {gf2(1), gf2(0)} == {gf2(1), gf2(0), gf2(1)};" << endl;
  assert(p_gf3.get_degree() == 2);
  assert(p_gf3 == gf_result);

  cout << "   TESTS PASSED!\n";
}

static void div_test(void) {
  cout << "\nDIV TESTS:\n";
  vector<double> coefficients = {1.15, 2.25, 3.35, 4.45, 5.55};
  vector<double> coefficients2 = {1.1, 2.2, 3.3, 4.4, 5.5};
  
  Polynomial<double> p(coefficients);
  Polynomial<double> q(coefficients2);
  Polynomial<double> r = (p / q);
  Polynomial<double> result = get<0>(p.divmod(q));

  cout << "   p / q == 1.00909" << endl;

  assert(r.get_degree() == 0);
  assert(r == result);

  GaloisField<TEST_PRIME> gf2(0);
  vector<GaloisField<TEST_PRIME>> gf_coeffs = {gf2(1), gf2(2), gf2(3), gf2(4), gf2(5)};
  vector<GaloisField<TEST_PRIME>> gf_coeffs2 = {gf2(1), gf2(2), gf2(3), gf2(4), gf2(5)};

  Polynomial<GaloisField<TEST_PRIME>> gf_p(gf_coeffs);
  Polynomial<GaloisField<TEST_PRIME>> gf_q(gf_coeffs2);

  Polynomial<GaloisField<TEST_PRIME>> gf_r = gf_p / gf_q;

  Polynomial<GaloisField<TEST_PRIME>> gf_result = get<0>(gf_p.divmod(gf_q));

  cout << "   gf_p / gf_q == 1" << endl;

  assert(gf_r.get_degree() == 0);
  assert(gf_r == gf_result);

   cout << "  TESTS PASSED!\n";
}

void comparisons_test(void) {
  cout << "\nCOMPARISONS TESTS:\n";
  vector<double> coefficients = {1.15, 2.25, 3.35, 4.45, 5.55};
  vector<double> coefficients2 = {1.1, 2.2, 3.3, 4.4, 5.5};

  Polynomial<double> p(coefficients);
  Polynomial<double> q(coefficients2);

  cout << "   p == p" << endl;
  assert(p == p);

  cout << "   p != q" << endl;
  assert(p != q);

  GaloisField<TEST_PRIME> gf2(0);
  vector<GaloisField<TEST_PRIME>> gf_coeffs = {gf2(1), gf2(2), gf2(3), gf2(4), gf2(5)};
  vector<GaloisField<TEST_PRIME>> gf_coeffs2 = {gf2(2), gf2(2), gf2(3), gf2(4), gf2(5)};

  Polynomial<GaloisField<TEST_PRIME>> gf_p(gf_coeffs);
  Polynomial<GaloisField<TEST_PRIME>> gf_q(gf_coeffs2);

  cout << "   gf_p == gf_p" << endl;
  assert(gf_p == gf_p);

  cout << "   gf_p != gf_q" << endl;
  assert(gf_p != gf_q);

  cout << "  TESTS PASSED" << endl;
}

void value_test(void) {
  cout << "\nVALUE TESTS:\n";

  vector<double> coefficients = {1.15, 2.25, 3.35, 4.45, 5.55};

  Polynomial<double> p(coefficients);

  cout << "   p(1) == 16.75" << endl;

  assert(p(1) == 16.75);

  GaloisField<TEST_PRIME> gf2(0);
  vector<GaloisField<TEST_PRIME>> gf_coeffs = {gf2(1), gf2(2), gf2(3), gf2(4), gf2(5)};
  Polynomial<GaloisField<TEST_PRIME>> gf_p(gf_coeffs);
  cout << "   gf_p(1) == 1" << endl;
  assert(gf_p(1) == gf2(15));

  cout << "  TESTS PASSED!\n";
}

int main(void) {
  constructor_test();
  add_test();
  sub_test();
  mul_test();
  div_test();
  comparisons_test();
  value_test();

  return 0;
}
