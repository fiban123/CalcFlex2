#pragma once

#include <gmp.h>
#include <mpfr.h>

#include <variant>
#include <optional>
#include <vector>
#include <iostream>

struct Rational{
    mpq_t q;

    Rational(const std::string zstr);
    ~Rational();

    // copy constructor
    Rational(Rational& other) = delete;
    // copy assignment
    Rational& operator=(const Rational& other) = delete;

    // move constructor
    Rational(Rational&& other);
    // move assignment
    Rational& operator=(Rational&& other) noexcept;
};

struct Real{
    mpfr_t r;

    Real(std::string rstr);
    ~Real();

    // copy constructor
    Real(Real& other) = delete;
    // copy assignment
    Real& operator=(const Real& other) = delete;

    // move constructor
    Real(Real&& other);
    // move assignment
    Real& operator=(Real&& other) noexcept;
};

struct DynamicReal{ // can be real or rational
    std::optional<std::variant<Rational, Real> > n; // real number or rational stored

    inline bool is_real(){return std::holds_alternative<Real>(*n);}
    inline bool is_rational(){return std::holds_alternative<Rational>(*n);}

    std::string get_str();

    DynamicReal() = delete;
    DynamicReal(std::string str);
};

struct DynamicVector{ // can store n-dimensional number
    std::vector<DynamicReal> dims; // dimensions of numbers

    std::string get_str();

    DynamicVector(std::string str, unsigned dim);
};

inline DynamicReal one_rational("1"); // constant; 1 as rational