### About

This repository contains programs written for my 2022/2023 university course *"Programming languages and paradigms"*.

Languages used: `C, Ada, Julia, Python, C++, Java, Haskell, Prolog, Go`.

### Paradigms

#### Procedural programming 

Iterative and recursive module implementation for the following functions in C, Ada and Julia:

- calculating factorial
- calculating greatest common divisor of two natural numbers
- solving the diophantine equation on integers

Wrappers of the above modules:

- C wrapper for Ada
- Ada wrapper for C
- Julia wrapper for C

#### Object-oriented programming

Implementation of a Galois field class in C++, Java and Python with operator overloading, exception handling and testing programs.

#### OOP and generics

Generic implementation of polynomial in C++, Java and Python with operator overloading, exception handling and testing programs. Polynomial's coefficients can be of type float or can be members of a Galois field.

C++ implementation of cyclic Hamming codes (7,4) using previously implemented polynomial and Galois field classes.

#### Logic / Functional programming

Implementation of the following functions in Prolog and Haskell:

- calculating factorial
- calculating greatest common divisor of two natural numbers
- solving the diophantine equation on integers

#### Concurrency

Implementation of the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in Go, Java and Ada with deadlock prevention by making one of the philosophers left-handed. Each solution has extensive logs and can be run with any number of philosophers and meals.
