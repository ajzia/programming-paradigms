#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <tuple>
#include <vector>
#include <sstream>
#include <cstdint>

using namespace std;

class OutOfBoundsException : public exception {
  private:
    string message;
 
  public:
    OutOfBoundsException (const char *file, const int line, int n) {
      ostringstream o;
      o << "\n" << file << ":" << line << ": " << "error: index i =" << to_string(n) << " is out of bounds.\n";
      message = o.str();
    }

    const char* what() const noexcept override {
      return const_cast<char*>(message.c_str());
    }
};

class ZeroDivisionError : public exception {
  private:
    string message = " ";
 
  public:
    ZeroDivisionError (const char *file, const int line) {
      ostringstream o;
      o << "\n" << file << ":" << line << ": " << "error: dividing by zero.\n";
      message = o.str();
    }
 
    const char* what() const noexcept override {
      return const_cast<char*>(message.c_str());
    }
};

template<typename T>
class Polynomial  {
  private:
    vector<T> coefficients;
    size_t degree;

    void remove_trailing_zeros() {
      size_t i = this->degree;
      while (i > 0 && this->coefficients[i] == T(0)) {
        this->coefficients.pop_back();
        this->degree--;
        i--;
      }
    }

  public:
    // Constructors
    Polynomial(void) {
      this->coefficients = {T(0)};
      this->degree = 0;
    }

    Polynomial(const vector<T> coeffs) {
      this->coefficients = coeffs;
      this->degree = coeffs.size() - 1;
      remove_trailing_zeros();
    }

    Polynomial(const T coeff) {
      this->degree = 0;
      this->coefficients = {coeff};
    }
    
    Polynomial(const Polynomial<T>& p) {
      this->coefficients = p.coefficients;
      this->degree = p.degree;
      remove_trailing_zeros();
    }

    T operator[](int64_t i) {
      if (i > degree || i < 0)
        throw OutOfBoundsException(__FILE__, __LINE__, i);
    
      return this->coefficients[i];
    }

    bool is_zero() const {
      return this->coefficients.size() == 1 && this->coefficients[0] == 0;
    }

    size_t get_degree(void) const {
      return degree;
    }

    // Arithmetic operators
    Polynomial<T> operator+ (const vector<T> coeffs) const;
    Polynomial<T> operator+ (const Polynomial<T> p) const;
    Polynomial<T> operator+ (const T coeff) const;

    Polynomial<T> operator- (const vector<T> coeffs) const;
    Polynomial<T> operator- (const Polynomial<T> p) const;
    Polynomial<T> operator- (const T coeff) const;

    Polynomial<T> operator* (const vector<T> coeffs) const;
    Polynomial<T> operator* (const Polynomial<T> p) const;
    Polynomial<T> operator* (const T coeff) const;

    T tail(void) const {
      return this->coefficients[this->degree];
    }
 
    tuple<Polynomial<T>, Polynomial<T>> divmod(Polynomial divisor) const {
      if (divisor.is_zero())
        throw ZeroDivisionError(__FILE__, __LINE__);

      Polynomial<T> quotient;
      Polynomial<T> remainder = *this;

      while (remainder.degree >= divisor.degree) {
        T coeff = remainder.tail() / divisor.tail();
        size_t degree = remainder.degree - divisor.degree;
        
        vector<T> new_coeffs(degree + 1, T(0));
        new_coeffs[degree] = coeff;

        Polynomial<T> new_polynomial(new_coeffs);
        quotient += new_polynomial;
        remainder = remainder - (divisor * new_polynomial);
      }

      return make_tuple(quotient, remainder);
    }

    Polynomial<T> operator/(const vector<T> coeffs) const;
    Polynomial<T> operator/(const Polynomial<T> p) const;
    Polynomial<T> operator/(const T singleton) const;

    // Modulo
    Polynomial<T> operator% (const vector<T> coeffs) const;
    Polynomial<T> operator% (const Polynomial<T> p) const;
    Polynomial<T> operator% (const T coeff) const;

    // Right arithmetic operators
    void operator+= (const vector<T> coeffs);
    void operator+= (const Polynomial<T> p);
    void operator+= (const T coeff);

    void operator-= (const vector<T> coeffs);
    void operator-= (const Polynomial<T> p);
    void operator-= (const T coeff);

    void operator*= (const vector<T> coeffs);
    void operator*= (const Polynomial<T> p);
    void operator*= (const T coeff);
  
    void operator/= (const vector<T> coeffs);
    void operator/= (const Polynomial<T> p);
    void operator/= (const T coeff);
    
    void operator%= (const vector<T> coeffs);
    void operator%= (const Polynomial<T> p);
    void operator%= (const T coeff);

    // Comparison operators
    bool operator== (const vector<T> coeffs) const;
    bool operator== (const Polynomial<T> p) const;
    bool operator== (const T coeff) const;

    bool operator!= (const vector<T> coeffs) const;
    bool operator!= (const Polynomial<T> p) const;
    bool operator!= (const T coeff) const;

    bool operator< (const vector<T> coeffs) const;
    bool operator< (const Polynomial<T> p) const;
    bool operator< (const T coeff) const;

    bool operator> (const vector<T> coeffs) const;
    bool operator> (const Polynomial<T> p) const;
    bool operator> (const T coeff) const;

    bool operator<= (const vector<T> coeffs) const;
    bool operator<= (const Polynomial<T> p) const;
    bool operator<= (const T coeff) const;

    bool operator>= (const vector<T> coeffs) const;
    bool operator>= (const Polynomial<T> p) const;
    bool operator>= (const T coeff) const;

    // Assignment operators
    void operator= (const vector<T> coeffs);
    void operator= (const Polynomial<T> p);
    void operator= (const T coeff);

    // Value of operator
    T operator() (const T value) const;

    friend ostream& operator<< (ostream& os, const Polynomial<T> p) {
      size_t i = 0;
      for (; i < p.get_degree(); i++)
        os << p.coefficients[i] << (i > 0 ? ("x^" + std::to_string(i)) : "") << " + ";

      os << p.coefficients[p.get_degree()] << (i > 0 ? ("x^" + std::to_string(i)) : "");

      return os;
    }
};

#endif
