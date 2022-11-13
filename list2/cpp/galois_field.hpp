#ifndef GALOISFIELD_H
#define GALOISFIELD_H

#include <iostream>
#include <cstdint>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

class PrimeException : public exception {
  private:
    string msg;

  public:
    PrimeException(const char *file, const int line) {
      ostringstream o;
      o << "\n" << file << ":" << line << ": " << "error: 'order' is not a prime number.\n";
      msg = o.str();
    }

    char* what() {
      return const_cast<char*>(msg.c_str());
    }
};

template <uint64_t order>
class GaloisField {
  private:
    uint64_t number;

    // Prime
    bool is_prime(const uint64_t num) {
      if (num == 2 || num == 3) return true;
      if (num < 2 || num % 2 == 0) return false;
      if (num < 9) return true;
      if (num % 3 == 0) return false;

      uint64_t sqrt_num = uint64_t(sqrt(num));
      uint64_t temp = 5;
      while (temp <= sqrt_num) {
        if (num % temp == 0) return false;
        if (num % (temp + 2) == 0) return false;
        temp += 6;
      }
      return true;
    }
    
  public:
    GaloisField(int64_t num) {
      try {
        if (is_prime(order))
          number = ((((num + order) % order) + order) % order);
        else 
          throw PrimeException(__FILE__, __LINE__);
      } catch (PrimeException& p) {
        cout << p.what();
        exit(3);
      }
    }
  
    // Arithmetic operators
    GaloisField<order> operator+ (const GaloisField<order> gf) const;
    GaloisField<order> operator- (const GaloisField<order> gf) const;
    GaloisField<order> operator* (const GaloisField<order> gf) const;
    GaloisField<order> operator/ (const GaloisField<order> gf) const;
    
    void operator+= (const GaloisField<order> gf);
    void operator-= (const GaloisField<order> gf);
    void operator*= (const GaloisField<order> gf);
    void operator/= (const GaloisField gf);
    
    // Incrementation
    void operator++ (void);
    void operator++ (int);
    void operator-- (void);
    void operator-- (int);

    // Comparison operators
    bool operator== (const GaloisField<order> gf) const;
    bool operator!= (const GaloisField<order> gf) const;
    bool operator> (const GaloisField<order> gf) const;
    bool operator< (const GaloisField<order> gf) const;
    bool operator>= (const GaloisField<order> gf) const;
    bool operator<= (const GaloisField<order> gf) const;

    // Assignment operator
    void operator= (const int64_t number) {
      this->number = (((number + order) % order) + order) % order;
    }

    // Output operator
    friend ostream& operator << (ostream& os, const GaloisField<order> gf) {
      os << "GF<" << order << ">(" << gf.number << ")";
      return os;
    }

    // Modular inverse
    int64_t mod_inv(const uint64_t a, const uint64_t b, const int64_t x = 1, const int64_t y = 0) {
      return b == 0 ? x : mod_inv(b, a % b, y, x - y * (a / b));
    }

    GaloisField<order> mod_inverse(void) {
      const int64_t temp = mod_inv(this->number, order);
      const uint64_t num = (((temp + order) % order) + order) % order;
      return GaloisField<order>(num);
    }

    // Getters
    uint64_t get_order(void) const;
    uint64_t get_number(void) const;
};

#endif 
