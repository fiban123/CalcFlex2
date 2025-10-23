#include "dynamic_vec.hpp"

#include <sstream>
#include <cstring>

void mp_string_remove_trailing_zeroes(std::string& s, long exp) {
    if (exp > s.length()){
        return;
    }

    // remove trailing zeroes
    long last_not_zero = (long) s.find_last_not_of('0');
    // make sure to not remove anything before the .
    last_not_zero = std::max(std::max(last_not_zero + 1, exp), 0L);
    s.erase(s.begin() + last_not_zero, s.end());
}

// convert a decimal floating-point value to something GMP can parse (e.g "1.1"
// -> "11/10")
std::string to_rational_string(std::string s) {
    std::string numerator;
    std::string denominator;

    size_t point_index = s.find('.');

    if (point_index == std::string::npos) {
        // point doesnt exist. just use denominator 1
        numerator = s;
        denominator = "1";
    }
    else {
        numerator = std::string(s.begin(), s.begin() + point_index);
        numerator += std::string(s.begin() + point_index + 1, s.end());

        denominator = '1';
        for (size_t i = 0; i < (s.length() - point_index - 1); i++) {
            denominator += '0';
        }
    }

    std::string out = numerator + "/" + denominator;

    return out;
}

std::string mpfr_get_str_normal(mpfr_t src, EvalConfig& config) {
    std::string out;

    size_t ndigits = mpfr_get_str_ndigits(10, config.representation_prec);

    mp_exp_t exp;
    char* mantissa_buf = mpfr_get_str(NULL, &exp, 10, ndigits - 2, src, MPFR_RNDN);

    if (config.auto_sci){
        if (exp > (ssize_t) config.auto_sci_threshold_n_digits){
            free(mantissa_buf);
            return mpfr_get_str_sci(src, config);
        }
    }

    std::string mantissa(mantissa_buf);

    mpfr_free_str(mantissa_buf);

    bool negative = mantissa[0] == '-';
    if (negative){
        mantissa = std::string(mantissa.begin() + 1, mantissa.end());
        out += '-';
    }

    mp_string_remove_trailing_zeroes(mantissa, exp);

    if (exp <= 0){
        //0.abc
        out += "0.";

        for (size_t i = 0; i < -exp; i++){
            out += '0';
        }

        out += mantissa;
    }
    else if (exp >= mantissa.length()){
        //abc0000
        out += mantissa;

        for (size_t i = 0; i < exp - mantissa.length(); i++){
            out += '0';
        }
    }
    else{
        //abc.abc
        out.append(mantissa.begin(), mantissa.begin() + exp);
        out += '.';
        out.append(mantissa.begin() + exp, mantissa.end());
    }

    out += 'f';

    return out;
}

std::string mpfr_get_str_sci(mpfr_t src, EvalConfig& config) {

    std::string out;

    mp_exp_t exp;
    char* mantissa_buf = mpfr_get_str(NULL, &exp, 10, config.sci_representation_n_digits, src, MPFR_RNDN);

    if (exp < config.sci_min_n_digits){
        free(mantissa_buf);
        return mpfr_get_str_normal(src, config);
    }

    std::string mantissa(mantissa_buf);

    mpfr_free_str(mantissa_buf);

    bool negative = mantissa[0] == '-';
    if (negative){
        mantissa = std::string(mantissa.begin() + 1, mantissa.end());
        out += '-';
    }

    mp_string_remove_trailing_zeroes(mantissa, exp);

    out += mantissa[0];
    out += '.';
    out.append(mantissa.begin() + 1, mantissa.end());

    out += exp >= 0 ? "e+" : "e";
    out += std::to_string(exp - 1);

    out += 'f';
    return out;
}

std::string mpz_get_str_sci(mpz_t src, EvalConfig& config) {
    if (mpz_sizeinbase(src, 10) < config.sci_min_n_digits){
        return mpz_get_str_normal(src);
    }

    std::string out;

    char* num_buf = mpz_get_str(NULL, 10, src);

    std::string num(num_buf);

    bool negative = num[0] == '-';
    if (negative){
        num = std::string(num.begin() + 1, num.end());
        out += '-';
    }

    size_t exp = num.length();

    if (num.length() > config.sci_representation_n_digits){
        num.resize(config.sci_representation_n_digits);
    }


    free(num_buf);

    mp_string_remove_trailing_zeroes(num, 1);

    out += num[0];
    out += '.';
    out.append(num.begin() + 1, num.end());

    out += "e+";
    out += std::to_string(exp - 1);

    return out;
}

std::string mpz_get_str_normal(mpz_ptr src){
    char* buf = mpz_get_str(NULL, 10, src);

    std::string str(buf);

    free(buf);

    return str;
}

std::string mpz_get_cppstr(mpz_t src, EvalConfig& config){
    if (config.auto_sci){
        if (mpz_sizeinbase(src, 10) > config.auto_sci_threshold_n_digits){
            return mpz_get_str_sci(src, config);
        }
    }

    if (config.out_representation_format == REPRESENTATION_FORMAT_SCI){
        return mpz_get_str_sci(src, config);
    }

    return mpz_get_str_normal(src);
}

std::string mpq_get_cppstr(mpq_t src, EvalConfig& config){

    if (mpq_is_den_one(src)){
        return mpz_get_cppstr(mpq_numref(src), config);
    }
    return mpz_get_cppstr(mpq_numref(src), config) + "/" + mpz_get_cppstr(mpq_denref(src), config);
}

std::string mpq_get_str_sci(mpq_t src, EvalConfig& config) {

    mpz_t one;
    mpz_init_set_ui(one, 1);

    mpz_t num;
    mpz_t den;

    mpz_inits(num, den, NULL);

    mpq_get_num(num, src);
    mpq_get_den(den, src);

    std::string numerator_str_sci = mpz_get_str_sci(num, config);

    if (mpz_cmp(den, one) == 0){
        // denominator is one
        return numerator_str_sci;
    }
    else{
        std::string denominator_str_sci = mpz_get_str_sci(den, config);

        return '(' + numerator_str_sci + '/' + denominator_str_sci + ')';
    }
}

bool mpq_is_den_one(mpq_ptr q){
    return mpz_cmp_ui(mpq_denref(q), 1) == 0;
}

DynamicNum to_float(DynamicNum& src) {
    DynamicNum n = src.deep_copy();

    n.to_float();

    return n;
}

void DynamicNum::set(DynamicNum& src) {
    if (src.type == FLOAT) {
        set_float(src.get_float());
    }
    else if (src.type == RATIONAL) {
        set_rational(src.get_rational());
    }
}

void DynamicNum::to_float() {
    if (type != RATIONAL) {
        return;
    }
    // convert rational to float
    MPFloat f;
    mpfr_init(&f);
    mpfr_set_q(&f, get_rational(), MPFR_RNDN);

    set_float(&f);
}

void DynamicNum::to_rational() {
    if (type != FLOAT) {
        return;
    }
    // convert float to rational
    MPRational q;
    mpq_init(&q);
    mpfr_get_q(&q, get_float());

    set_rational(&q);
}

std::string DynamicNum::get_str(EvalConfig& config) {
    if (type == NONE) {
        return "none";
    }
    std::ostringstream out;

    if (type == FLOAT) {
        MPFloat* f = get_float();
        if (config.out_representation_format == REPRESENTATION_FORMAT_NORMAL) {
            out << mpfr_get_str_normal(f, config);
        }
        else {
            out << mpfr_get_str_sci(f, config);
        }
    }
    else {
        // rational
        MPRational* q = get_rational();

        if (config.out_representation_type == REPRESENTATION_TYPE_EXACT) {
            // exact
            if (config.out_representation_format == REPRESENTATION_FORMAT_NORMAL){
                // normal
                out << mpq_get_cppstr(q, config);
            }
            else{
                out << mpq_get_str_sci(q, config);
            }
        }
        else {
            // float
            // convert rational to float
            mpfr_t f;
            mpfr_init2(f, config.representation_prec);
            mpfr_set_q(f, q, MPFR_RNDN);

            if (config.out_representation_format == REPRESENTATION_FORMAT_NORMAL){
                // normal
                out << mpfr_get_str_normal(f, config);
            }
            else{
                // sci
                out << mpfr_get_str_sci(f, config);
            }

            mpfr_clear(f);
        }
    }

    return out.str();
}

DynamicNum DynamicNum::deep_copy() {
    DynamicNum copy;
    if (type == FLOAT) {
        MPFloat* f = get_float();
        MPFloat f_copy;

        mpfr_init2(&f_copy, mpfr_get_prec(f));
        mpfr_set(&f_copy, f, MPFR_RNDN);
        copy.set_float(&f_copy);
    }
    else if (type == RATIONAL) {
        MPRational* q = get_rational();
        MPRational q_copy;

        mpq_init(&q_copy);
        mpq_set(&q_copy, q);

        copy.set_rational(&q_copy);
    }
    return copy;
}

DynamicNum::DynamicNum(std::string str) {
    std::cout << "new dynamicnum" << std::endl;

    std::string rational_string = to_rational_string(str);

    // always initialize strings as rationals
    MPRational q;

    mpq_init(&q);
    mpq_set_str(&q, rational_string.c_str(), 10);
    mpq_canonicalize(&q);
    ;

    set_rational(&q);
}

DynamicNum::DynamicNum() {
    // initialize with rational 1 as default
    MPRational q;

    mpq_init(&q);
    mpq_set_ui(&q, 1, 1);
    // no need to canonicalize
    set_rational(&q);
}

std::string DynamicVec::get_str_long(EvalConfig& config) {
    std::ostringstream out;

    if (dims.empty()) {
        return "empty vec";
    }

    for (unsigned i = 0; i < dims.size(); i++) {
        out << dims[i].get_str(config) << " [" << i << "]";
        if (i != dims.size() - 1) {
            out << " +\\\n";
        }
    }

    return out.str();
}

std::string DynamicVec::get_str_short(EvalConfig& config) {
    std::ostringstream out;

    if (dims.empty()) {
        return "empty";
    }
    if (dims.size() > 1){
        out << '(';
    }
    for (unsigned i = 0; i < dims.size(); i++) {
        out << dims[i].get_str(config);
        if (i != dims.size() - 1) {
            out << " and ";
        }
    }
    if (dims.size() > 1){
        out << ')';
    }

    return out.str();
}

void DynamicVec::set_dims(unsigned ndims) {
    int diff = (int)ndims - (int)dims.size();

    if (diff > 0) {
        for (unsigned i = 0; i < diff; i++) {
            dims.emplace_back();
        }
    }
    else if (diff < 0) {
        // check if this leaks memory
        for (unsigned i = ndims; i < dims.size(); i++) {
            dims[i - 1].clear();
        }
        dims.erase(dims.begin() + ndims, dims.end());
    }
}

void DynamicVec::set_dim(DynamicNum& n, unsigned dim) {
    if (dim + 1 > dims.size()) {
        set_dims(dim + 1);
    }
    dims[dim].set(n);
}

void DynamicVec::deep_copy_from(DynamicVec& src) {}

DynamicVec::DynamicVec(std::string str, unsigned dim) {
    if (dim == 0) {
        dims.emplace_back(str);
        return;
    }

    set_dims(dim);

    dims.emplace_back(str);
}

DynamicVec::DynamicVec(DynamicNum& n, unsigned dim) {
    if (dim == 0) {
        dims.emplace_back(n);
        return;
    }

    for (unsigned i = 0; i < dim; i++) {
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

DynamicVec::~DynamicVec() {
    std::cout << "destructing" << get_str_short(eval_config) << "...";
    for (size_t i = 0; i < dims.size(); i++) {
        dims[i].clear();
    }
    std::cout << "D" << std::endl;
}
