#include "galois_field.hpp"

// Arithmetic operators
template<uint64_t order>
GaloisField<order> GaloisField<order>::operator+ (const GaloisField<order> gf) const {
  uint64_t new_num = (order + ((number + gf.number + order) % order)) % order;
  return GaloisField<order>(new_num);
}

template<uint64_t order>
GaloisField<order> GaloisField<order>::operator- (const GaloisField<order> gf) const {
  uint64_t new_num = (order + ((number - gf.number + order) % order)) % order;
  return GaloisField<order>(new_num);
}

template<uint64_t order>
GaloisField<order> GaloisField<order>::operator* (const GaloisField<order> gf) const {
  uint64_t new_num = (order + ((number * gf.number + order) % order)) % order;
  return GaloisField<order>(new_num);
}

template<uint64_t order>
GaloisField<order> GaloisField<order>::operator/ (GaloisField<order> gf) const {
  return (*this * gf.mod_inverse());
}

// Incrementation
template<uint64_t order>
void GaloisField<order>::operator++ (void) { // prefix ++
  GaloisField<order> gf(1);
  *this = (*this + gf);
}

template<uint64_t order>
void GaloisField<order>::operator++ (int) { // postfix ++
  GaloisField<order> gf(1);
  *this = (*this + gf);
}

template<uint64_t order>
void GaloisField<order>::operator-- (void) { // prefix --
  GaloisField<order> gf(1);
  *this = (*this - gf);
}

template<uint64_t order>
void GaloisField<order>::operator-- (int) { // postfix --
  GaloisField<order> gf(1);
  *this = (*this - gf);
}

// i-arithmetic 
template<uint64_t order>
void GaloisField<order>::operator+= (const GaloisField<order> gf) { 
  *this = (*this + gf);
}

template<uint64_t order>
void GaloisField<order>::operator-= (const GaloisField<order> gf) { 
  *this = (*this - gf);
}

template<uint64_t order>
void GaloisField<order>::operator*= (const GaloisField<order> gf) { 
  *this = (*this * gf);
}

template<uint64_t order>
void GaloisField<order>::operator/= (const GaloisField<order> gf) { 
  *this = (*this / gf);
}

// Comparison operators
template<uint64_t order>
bool GaloisField<order>::operator== (const GaloisField<order> gf) const {
  return (number == gf.number);
}

template<uint64_t order>
bool GaloisField<order>::operator!= (const GaloisField<order> gf) const {
  return (number != gf.number);
}

template<uint64_t order>
bool GaloisField<order>::operator> (const GaloisField<order> gf) const {
  return (number > gf.number);
}

template<uint64_t order>
bool GaloisField<order>::operator< (const GaloisField<order> gf) const {
  return (number < gf.number);
}

template<uint64_t order>
bool GaloisField<order>::operator>= (const GaloisField<order> gf) const {
  return (number >= gf.number);
}

template<uint64_t order>
bool GaloisField<order>::operator<= (const GaloisField<order> gf) const {
  return (number <= gf.number);
}

template<uint64_t order>
uint64_t GaloisField<order>::get_order(void) const{
  return order;
}

template<uint64_t order>
uint64_t GaloisField<order>::get_number(void) const {
  return number;
}