#pragma once

#include <gmp.h>
#include <mpfr.h>

#include <variant>
#include <vector>
#include <iostream>

inline Rational one_rational("1"); // constant; 1 as rational

struct Rational{
    mpz_t z;

    Rational(const std::string zstr);
    ~Rational();

    // copy constructor
    Rational(const Rational& other);

    // copy assignment
    Rational& operator=(const Rational& other) = delete;
};

struct Real{
    mpfr_t r;

    Real(std::string rstr);
    ~Real();

    // copy constructor
    Real(const Real& other);

    // copy assignment
    Real& operator=(const Real& other) = delete;
};

struct DynamicReal{ // can be real or rational
    std::variant<Rational, Real> n; // real number or rational stored

    inline bool is_real(){return std::holds_alternative<Real>(n);}
    inline bool is_rational(){return std::holds_alternative<Rational>(n);}

    std::string get_str();

    DynamicReal() = delete;
    DynamicReal(std::string str);
};

struct DynamicVector{ // can store n-dimensional number
    std::vector<DynamicReal> dims; // dimensions of numbers

    DynamicVector(std::string str, unsigned dim);
}