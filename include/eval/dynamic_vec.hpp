#pragma once

#include <gmp.h>
#include <mpfr.h>

#include <iostream>
#include <memory>
#include <optional>
#include <variant>
#include <vector>

#include "eval_config.hpp"

typedef __mpfr_struct MPFloat;
typedef __mpq_struct MPRational;

enum NumType { NONE, FLOAT, RATIONAL };
void mp_string_remove_trailing_zeroes(std::string& s, long exp);

std::string to_rational_string(std::string s);

std::string mpfr_get_str_normal(mpfr_t src, EvalConfig& config);

std::string mpfr_get_str_sci(mpfr_t src, EvalConfig& config);

std::string mpz_get_str_sci(mpz_t src, EvalConfig& config);

std::string mpz_get_str_normal(mpz_ptr src);

std::string mpz_get_cppstr(mpz_t src, EvalConfig& config);

std::string mpq_get_cppstr(mpq_t src, EvalConfig& config);

std::string mpq_get_str_sci(mpq_t src, EvalConfig& config);

bool mpq_is_den_one(mpq_ptr q);

struct DynamicNum {  // can be real or rational
    void* nptr = nullptr;
    NumType type = NONE;

    inline size_t get_size() { return type == FLOAT ? sizeof(MPFloat) : sizeof(MPRational); }

    inline MPFloat* get_float() { return reinterpret_cast<MPFloat*>(nptr); }
    inline MPRational* get_rational() { return reinterpret_cast<MPRational*>(nptr); }

    inline void clear() {
        std::cout << "clear" << std::endl;
        if (nptr) {
            if (type == FLOAT) {
                std::cout << "float C" << std::endl;
                MPFloat* f = get_float();
                mpfr_clear(f);
            }
            else if (type == RATIONAL) {
                std::cout << "rational C" << std::endl;
                MPRational* q = get_rational();
                mpq_clear(q);
            }
            if (nptr) {
                free(nptr);
                ;
                ;
            }
        }
        type = NONE;
    }

    inline void set_float(MPFloat* f) {
        clear();
        nptr = malloc(sizeof(MPFloat));
        memcpy(nptr, f, sizeof(MPFloat));
        type = FLOAT;
    }
    inline void set_rational(MPRational* q) {
        clear();
        nptr = malloc(sizeof(MPRational));
        memcpy(nptr, q, sizeof(MPRational));
        type = RATIONAL;
    }

    void set(DynamicNum& src);

    void to_float();
    void to_rational();

    std::string get_str(EvalConfig& config);

    DynamicNum deep_copy();

    DynamicNum(std::string str);

    DynamicNum();
};

struct DynamicVec {  // can store n-dimensional numbers
    std::vector<DynamicNum> dims;

    std::string get_str_long(EvalConfig& config);

    std::string get_str_short(EvalConfig& config);

    void set_dims(unsigned ndinms);

    void set_dim(DynamicNum& n, unsigned dim);

    void deep_copy_from(DynamicVec& src);

    DynamicVec(std::string str, unsigned dim);

    DynamicVec(DynamicNum& n, unsigned dim);

    DynamicVec() = default;
    // copy
    DynamicVec(const DynamicVec& other) = delete;
    // move
    DynamicVec(DynamicVec&& other) = delete;

    ~DynamicVec();
};

typedef std::unique_ptr<DynamicVec> DynamicVecPtr;

DynamicNum to_float(DynamicNum& src);
