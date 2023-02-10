#include "polynomial.hpp"

// Arithmetic operators
template<typename T>
Polynomial<T> Polynomial<T>::operator+ (const vector<T> coeffs) const {
  size_t this_size = this->degree + 1;
  size_t coeffs_size = coeffs.size();
  size_t new_size = max(this_size, coeffs_size);
  vector<T> new_coeffs;

  for (size_t i = 0; i < new_size; i++) {
    T a = 0, b = 0;
    if (i < this_size) 
      a = this->coefficients[i];
    if (i < coeffs_size)
      b = coeffs[i];
    new_coeffs.push_back(T(a + b));
  }

  return Polynomial<T>(new_coeffs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator+ (const Polynomial<T> p) const {
  return *this + p.coefficients;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator+ (const T coeff) const {
  vector<T> new_coeffs = this->coefficients;
  new_coeffs[0] = T(new_coeffs[0] + coeff);
  return Polynomial<T>(new_coeffs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator- (const vector<T> coeffs) const {
  size_t this_size = this->degree + 1;
  size_t coeffs_size = coeffs.size();
  size_t new_size = max(this_size, coeffs_size);
  vector<T> new_coeffs;

  for (size_t i = 0; i < new_size; i++) {
    T a = 0, b = 0;
    if (i < this_size) 
      a = this->coefficients[i];
    if (i < coeffs_size)
      b = coeffs[i];
    new_coeffs.push_back(T(a - b));
  }

  return Polynomial<T>(new_coeffs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator- (const Polynomial<T> p) const {
  return *this - p.coefficients;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator- (const T coeff) const {
  vector<T> new_coeffs = this->coefficients;
  new_coeffs[0] = T(new_coeffs[0] - coeff);
  return Polynomial<T>(new_coeffs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator* (const vector<T> coeffs) const {
  if (this->is_zero() || (coeffs.size() == 1 && coeffs[0] == T(0)))
    return Polynomial<T>(T(0));

  vector<T> new_coeffs(this->degree + coeffs.size(), T(0));

  for (size_t i = 0; i <= this->degree; i++)
    for (size_t j = 0; j < coeffs.size(); j++)
      new_coeffs[i + j] += this->coefficients[i] * coeffs[j];

  return Polynomial<T>(new_coeffs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator* (const Polynomial<T> p) const {
  return *this * p.coefficients;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator* (const T coeff) const {
  return *this * vector<T>{coeff};
}

 
template<typename T>
Polynomial<T> Polynomial<T>::operator/(const vector<T> coeffs) const {
  if (coeffs.size() == 1 && coeffs[0] == 0)
    throw ZeroDivisionError(__FILE__, __LINE__);
 
  if (this->is_zero())
    return Polynomial<T>(T(0));
 
  return get<0>(this->divmod(coeffs));
}
 
template<typename T>
Polynomial<T> Polynomial<T>::operator/(const Polynomial<T> p) const {
  return *this / p.coefficients;
}
 
template<typename T>
Polynomial<T> Polynomial<T>::operator/(const T singleton) const {
  return *this / vector<T>{singleton};
}

template<typename T>
Polynomial<T> Polynomial<T>::operator% (const vector<T> coeffs) const {
  if (coeffs.size() == 1 && coeffs[0] == 0)
    throw ZeroDivisionError(__FILE__, __LINE__);
 
  if (this->is_zero())
    return Polynomial<T>(T(0));
 
  return get<1>(this->divmod(coeffs));
}

template<typename T>
Polynomial<T> Polynomial<T>::operator% (const Polynomial<T> p) const {
  return *this % p.coefficients;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator% (const T coeff) const {
  return *this % vector<T>{coeff};
}

// Right arithmetic operators
template<typename T>
void Polynomial<T>::operator+= (const vector<T> coeffs) {
  *this = *this + coeffs;
}

template<typename T>
void Polynomial<T>::operator+= (const Polynomial<T> p) {
  *this = *this + p.coefficients;
}

template<typename T>
void Polynomial<T>::operator+= (const T coeff) {
  *this = *this + coeff;
}


template<typename T>
void Polynomial<T>::operator-= (const vector<T> coeffs) {
  *this = *this - coeffs;
}

template<typename T>
void Polynomial<T>::operator-= (const Polynomial<T> p) {
  *this = *this - p.coefficients;
}

template<typename T>
void Polynomial<T>::operator-= (const T coeff) {
  *this = *this - coeff;
}

template<typename T>
void Polynomial<T>::operator*= (const vector<T> coeffs) {
  *this = *this * coeffs;
}

template<typename T>
void Polynomial<T>::operator*= (const Polynomial<T> p) {
  *this = *this * p.coefficients;
}

template<typename T>
void Polynomial<T>::operator*= (const T coeff) {
  *this = *this * vector<T>{coeff};
}

template<typename T>
void Polynomial<T>::operator/= (const vector<T> coeffs) {
  *this = *this / coeffs;
}

template<typename T>
void Polynomial<T>::operator/= (const Polynomial<T> p) {
  *this = *this / p.coefficients;
}

template<typename T>
void Polynomial<T>::operator/= (const T coeff) {
  *this = *this / vector<T>{coeff};
}

template<typename T>
void Polynomial<T>::operator%= (const vector<T> coeffs) {
  *this = *this % coeffs;
}

template<typename T>
void Polynomial<T>::operator%= (const Polynomial<T> p) {
  *this = *this % p.coefficients;
}

template<typename T>
void Polynomial<T>::operator%= (const T coeff) {
  *this = *this % vector<T>{coeff};
}

// Comparison operators
template<typename T>
bool Polynomial<T>::operator== (const vector<T> coeffs) const {
  return this->coefficients == coeffs;
}

template<typename T>
bool Polynomial<T>::operator== (const Polynomial<T> p) const {
  return *this == p.coefficients;
}

template<typename T>
bool Polynomial<T>::operator== (const T coeff) const {
  return this->coefficients == vector<T>{coeff};
}

template<typename T>
bool Polynomial<T>::operator!= (const vector<T> coeffs) const {
  return ! (*this == coeffs);
}

template<typename T>
bool Polynomial<T>::operator!= (const Polynomial<T> p) const {
  return ! (*this == p.coefficients);
}

template<typename T>
bool Polynomial<T>::operator!= (const T coeff) const {
  return ! (*this == vector<T>{coeff});
}

template<typename T>
bool Polynomial<T>::operator<(const vector<T> coeffs) const
{
  if (this->degree < coeffs.size() - 1)
    return true;
  else if (this->degree > coeffs.size() - 1)
    return false;
  
  for (size_t i = this->degree; i >= 0; i--)
    if (this->coefficients[i] < coeffs[i])
      return true;
    else if (this->coefficients[i] > coeffs[i])
      return false;

  return false;
}

// <
template<typename T>
bool Polynomial<T>::operator< (const Polynomial<T> p) const {
  return *this < p.coefficients;
}

template<typename T>
bool Polynomial<T>::operator< (const T coeff) const {
  if (this->is_zero() && coeff == T{0})
    return false;
  
  if (this->degree > 0)
    return true;

  return this->coefficients[0] < coeff;
}

template<typename T>
bool Polynomial<T>::operator> (const vector<T> coeffs) const {
  return ! (*this < coeffs) && ! (*this == coeffs);
}

template<typename T>
bool Polynomial<T>::operator> (const Polynomial<T> p) const {
  return ! (*this < p.coefficients) && ! (*this == p.coefficients);
}

template<typename T>
bool Polynomial<T>::operator> (const T coeff) const {
  return (*this < coeff) && ! (*this == coeff);
}

template<typename T>
bool Polynomial<T>::operator<= (const vector<T> coeffs) const {
  return ! (*this > coeffs);
}

template<typename T>
bool Polynomial<T>::operator<= (const Polynomial<T> p) const {
  return ! (*this > p.coefficients);
}

template<typename T>
bool Polynomial<T>::operator<= (const T coeff) const {
  return ! (*this > coeff);
}

template<typename T>
bool Polynomial<T>::operator>= (const vector<T> coeffs) const {
  return ! (*this < coeffs);
}

template<typename T>
bool Polynomial<T>::operator>= (const Polynomial<T> p) const {
  return ! (*this < p.coefficients);
}

template<typename T>
bool Polynomial<T>::operator>= (const T coeff) const {
  return ! (*this < coeff);
}

template<typename T>
void Polynomial<T>::operator= (const vector<T> coeffs) {
  *this = Polynomial<T>(coeffs);
}

template<typename T>
void Polynomial<T>::operator= (const Polynomial<T> p) {
  this->coefficients = p.coefficients;
  this->degree = p.degree;
}

template<typename T>
void Polynomial<T>::operator= (const T coeff) {
  *this = Polynomial<T>(coeff);
}

template<typename T>
T Polynomial<T>::operator()(const T val) const {
  T result = 0;
  T temp_val = 1;
  for (int i = 0; i < this->coefficients.size(); i++)
  {
    result += this->coefficients[i] * temp_val;
    temp_val *= val;
  }
  return result;
}
