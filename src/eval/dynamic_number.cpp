#include "dynamic_number.hpp"


Rational::Rational(std::string zstr){
    mpq_init(q);
    mpq_set_str(q, zstr.c_str(), 10);
    mpq_canonicalize(q);
}

Rational::~Rational(){
    mpq_clear(q);
}

Rational::Rational(Rational &&other){
    std::cout << "move constructor rational\n";
    mpq_init(q);
    mpq_set(q, other.q);
}

Rational &Rational::operator=(Rational &&other) noexcept{
    std::cout << "move assignment rational\n";
    if (this != &other) {
        mpq_set(q, other.q);
    }
    return *this;
}


Real::Real(std::string rstr){
    std::cout << "move constructor real\n";
    mpfr_init_set_str(r, rstr.c_str(), 10, MPFR_RNDN);
}

Real::~Real(){
    mpfr_clear(r);
}

Real::Real(Real &&other){
    std::cout << "move assignment real\n";
    mpfr_init2(r, mpfr_get_prec(other.r));
    mpfr_set(r, other.r, MPFR_RNDN);
}

Real &Real::operator=(Real &&other) noexcept{
    if (this != &other) {
        mpfr_set(r, other.r, MPFR_RNDN);
    }
    return *this;
}


std::string DynamicReal::get_str() {
    if (std::holds_alternative<Rational>(*n)){
        Rational& q = std::get<Rational>(*n);
        std::cout << "yo1\n";
        return std::string(mpq_get_str(NULL, 10, q.q));
    }
    else if (std::holds_alternative<Real>(*n)){
        Real& r = std::get<Real>(*n);
        std::cout << "yo2\n";
    }
    return "";
}

DynamicReal::DynamicReal(std::string str){
    n = Rational(str);
    std::cout << "initdynreal\n";
}

std::string DynamicVector::get_str() {
    if (dims.empty()) return "";
    return dims[0].get_str();
}

DynamicVector::DynamicVector(std::string str, unsigned dim){
    if (dim == 0){
        std::cout << "initdynvector\n";
        dims.emplace_back<DynamicReal>(str);
    }
    else{
        // initialize with 1 up to dim
        for (unsigned i = 0; i < dim - 1; i++){
            //dims.emplace_back(one_rational);
        }
        //dims.emplace_back(str);
    }
}
