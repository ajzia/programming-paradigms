/*
*  g++ hamming.cpp galois_field.cpp polynomial.cpp && ./a.out
*/

#include "galois_field.cpp"
#include "polynomial.cpp"
#include <iostream>
#include <cassert>
#include <map>

using namespace std;

#define MESSAGE_LENGTH 4
#define CODEWORD_LENGTH 7

template<typename T> // Polynomial<GaloisField<2>>
class Hamming {
  private: 
    T message;
    T modulus;
    T generator;
    map<T, T> codebook;

    T int_to_gf2(size_t number) {
      if (number == 0)
        return T(0);
      
      vector<GaloisField<2>> coefficients;
      while (number > 0) {
        coefficients.push_back(GaloisField<2>(number));
        number /= 2;
      }
      
      return T(coefficients);
    }

  public: 
    // constructor
    Hamming(T message, T modulus, T generator) {
      this->message = message;
      this->modulus = modulus;
      this->generator = generator;
    }

    // returns codeword
    T hamming_encoder(T message) {
      if (message.get_degree() > MESSAGE_LENGTH - 1)
        throw "Message degree is too high";
      if (generator.get_degree() > CODEWORD_LENGTH - MESSAGE_LENGTH)
        throw "Generator degree is too high";
      return (message * this->generator) % this->modulus;
    }

    T xn(size_t degree) {
      vector<GaloisField<2>> coefficients(degree + 1, GaloisField<2>(0));
      coefficients[degree] = GaloisField<2>(1);
      return T(coefficients);
    }

    // makes codebook
    map<T, T> hamming_codebook() {
      map<T, T> codebook;
      for (size_t i = 0; i < pow(2, MESSAGE_LENGTH); i++) {
        T message  = int_to_gf2(i);
        T codeword = hamming_encoder(message);
        codebook[codeword] = message;

        for (size_t j = 0; j < CODEWORD_LENGTH; j++) {
          T codeword_with_error = codeword;
          codeword_with_error = codeword_with_error + xn(j);
          codebook[codeword_with_error] = message;
        }
      }

      return codebook;
    }

    // returns message
    T hamming_decoder(T codeword) {
      if (codebook.find(codeword) == codebook.end())
        throw "Codeword not found.";
      return codebook[codeword];
    }

    T get_message() {
      return this->message;
    }

    T get_modulus() {
      return this->modulus;
    }

    T get_generator() {
      return this->generator;
    }

};


int main(void) {
  GaloisField<2> one  = GaloisField<2>(1);
  GaloisField<2> zero = GaloisField<2>(0);

  Polynomial<GaloisField<2>> generator({one, one, zero, one}); // 1 + x + x^3
  Polynomial<GaloisField<2>> message({one, one, zero, one}); // 1 + x + x^3
  Polynomial<GaloisField<2>> modulus({one, zero, zero, zero, zero, zero, zero, one}); // 1 + x^7
  
  Hamming<Polynomial<GaloisField<2>>> hamming(message, modulus, generator);

  cout << "Message: " << hamming.get_message() << endl;
  cout << "Modulus: " << hamming.get_modulus() << endl;
  cout << "Generator: " << hamming.get_generator() << endl << endl;

  map<Polynomial<GaloisField<2>>, Polynomial<GaloisField<2>>> table = hamming.hamming_codebook();

  Polynomial<GaloisField<2>> codeword = hamming.hamming_encoder(hamming.get_message());
  cout << "Codeword (message * generator): " << codeword << endl;

  Polynomial<GaloisField<2>> distorted = codeword + hamming.xn(0); // 1 bit error
  cout << "Distorted (codeword + 1): " << distorted << endl;
  cout << "Distorred message: " << table[distorted] << endl;

  Polynomial<GaloisField<2>> distorted2 = codeword + hamming.xn(1) + hamming.xn(3); // 2 bit error

  cout << "Distorted (codeword + x + x^3): " << distorted2 << endl;
  cout << "Distorred message: " << table[distorted2] << endl;


  return 0;
}
