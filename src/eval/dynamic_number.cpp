#include "dynamic_number.hpp"


Rational::Rational(std::string zstr){
    mpz_init_set_str(z, zstr.c_str(), 10);
}

Rational::~Rational(){
    mpz_clear(z);
}

Rational::Rational(const Rational &other){
    mpz_init_set(z, other.z);
}


Real::Real(std::string rstr){
    mpfr_init_set_str(r, rstr.c_str(), 10, MPFR_RNDN);
}

Real::~Real(){
    mpfr_clear(r);
}

Real::Real(const Real &other){
    mpfr_init_set(r, other.r, MPFR_RNDN);
}

std::string DynamicReal::get_str(){
    char* str;
    if (is_real()){
        Real& r = std::get<Real>(n);
        mpfr_get_str(NULL, NULL, 10, 50, r.r, MPFR_RNDN);
    }
}

DynamicReal::DynamicReal(std::string str)
    : n(Rational(str)) {} // strings are always initialized as rational

DynamicVector::DynamicVector(std::string str, unsigned dim){
    if (dim == 0){
        dims.emplace_back(str);
    }
    else{
        // initialize with 1 up to dim
        for (unsigned i = 0; i < dim - 1; i++){
            dims.emplace_back<Rational>(one_rational);
        }
        dims.emplace_back(str);
    }
}
