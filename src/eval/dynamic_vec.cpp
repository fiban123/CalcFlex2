#include "dynamic_vec.hpp"

void copy_mpq(mpq_t dest, mpq_t src){
    mpq_init(dest);
    mpq_set(dest, src);
}

void copy_mpfr(mpfr_t dest, mpfr_t src){
    mpfr_init2(dest, mpfr_get_prec(src));
    mpfr_set(dest, src, MPFR_RNDN);
}

// convert a decimal floating-point value to something GMP can parse (e.g "1.1" -> "11/10")
std::string to_rational_string(std::string s){

    std::string numerator;
    std::string denominator;

    size_t point_index = s.find('.');


    if (point_index == std::string::npos){
        // point doesnt exist. just use denominator 1
        numerator = s;
        denominator = "1";
    }
    else{
        numerator = std::string(s.begin(), s.begin() + point_index);
        numerator += std::string (s.begin() + point_index + 1, s.end());

        denominator = '1';
        for (size_t i = 0; i < (s.length() - point_index - 1); i++){
            denominator += '0';
        }
    }

    std::string out = numerator + "/" + denominator;

    return out;
}

void DynamicNum::set(DynamicNum &src){
    if (src.type == FLOAT){
        set_float(src.get_float());
    }
    else if (src.type == RATIONAL){
        set_rational(src.get_rational());
    }
}

void DynamicNum::to_float()
{
    if (type != RATIONAL){
        return;
    }
    // convert rational to float
    MPFloat f;
    mpfr_init(&f);
    mpfr_set_q(&f, get_rational(), MPFR_RNDN);

    set_float(&f);
}

void DynamicNum::to_rational(){
    if (type != FLOAT){
        return;
    }
    // convert float to rational
    MPRational q;
    mpq_init(&q);
    mpfr_get_q(&q, get_float());

    set_rational(&q);
}

std::string DynamicNum::get_str()
{
    char* buf = nullptr;
    if (type == NONE){
        return "none";
    }
    if (type == FLOAT){
        MPFloat* f = get_float();
        buf = mpfr_get_str(NULL, NULL, 10, 10, f, MPFR_RNDN);
    }
    else if (type == RATIONAL){
        MPRational* q = get_rational();
        buf = mpq_get_str(NULL, 10, q);
    }
    return std::string(buf);
}

DynamicNum DynamicNum::deep_copy(){
    DynamicNum copy;
    if (type == FLOAT){
        MPFloat* f = get_float();
        MPFloat f_copy;

        mpfr_init2(&f_copy, mpfr_get_prec(f));
        mpfr_set(&f_copy, f, MPFR_RNDN);
        copy.set_float(&f_copy);
    }
    else if (type == RATIONAL){
        MPRational* q = get_rational();
        MPRational q_copy;

        mpq_init(&q_copy);
        mpq_set(&q_copy, q);

        copy.set_rational(&q_copy);
    }
    return copy;
}

DynamicNum::DynamicNum(std::string str){
    std::string rational_string = to_rational_string(str);

    //always initialize strings as rationals
    MPRational q;

    mpq_init(&q);
    mpq_set_str(&q, rational_string.c_str(), 10);
    mpq_canonicalize(&q);;

    set_rational(&q);
}

DynamicNum::DynamicNum(){
    // initialize with rational 1 as default
    MPRational q;

    mpq_init(&q);
    mpq_set_ui(&q, 1, 1);
    // no need to canonicalize
    set_rational(&q);
}

void DynamicVec::print_long(){

    if (dims.empty()){
        std::cout << "empty vec\n";
        return;
    }

    for (unsigned i = 0; i < dims.size(); i++){
        std::cout << dims[i].get_str() << " [" << i << "]";
        if (i != dims.size() - 1){
            std::cout << " +\\\n";
        }
    }
    std::cout << "\n\n";
}

void DynamicVec::print_short(){
    if (dims.empty()){
        std::cout << "empty";
        return;
    }
    for (unsigned i = 0; i < dims.size(); i++){
        std::cout << dims[i].get_str() << "[" << i << "]";
        if (i != dims.size() - 1){
            std::cout << " and ";
        }
    }

}

void DynamicVec::set_dims(unsigned ndims){
    int diff = (int) ndims - (int) dims.size();

    if (diff > 0){
        for (unsigned i = 0; i < diff; i++){
            dims.emplace_back();
        }
    }
    else if (diff < 0){
        // check if this leaks memory
        for (unsigned i = ndims; i < dims.size(); i++){
            dims[i - 1].clear();
        }
        dims.erase(dims.begin() + ndims, dims.end());
    }
}

void DynamicVec::set_dim(DynamicNum& n, unsigned dim){
    if (dim + 1 > dims.size()){
        set_dims(dim + 1);
    }
    dims[dim].set(n);
}

void DynamicVec::deep_copy_from(DynamicVec &src)
{
}

DynamicVec::DynamicVec(std::string str, unsigned dim)
{
    if (dim == 0){
        dims.emplace_back(str);
        return;
    }

    set_dims(dim);

    dims.emplace_back(str);
}

DynamicVec::DynamicVec(DynamicNum& n, unsigned dim){
    if (dim == 0){
        dims.emplace_back(n);
        return;
    }

    for (unsigned i = 0; i < dim; i++){
        dims.emplace_back(); // default-constructed dynamicnum
    }
    dims.emplace_back(n);
}

/*
DynamicVec::DynamicVec(const DynamicVec &other){
    print_short();
    std::cout << " copied\n";
}

DynamicVec::DynamicVec(DynamicVec &&other){
    print_short();
    std::cout << " moved\n";
}*/

DynamicVec::~DynamicVec()
{
    for (size_t i = 0; i < dims.size(); i++){
        dims[i].clear();
    }
    print_short();
    std::cout << " destructed\n";
}
