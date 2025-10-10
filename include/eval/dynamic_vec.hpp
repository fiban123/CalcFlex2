#pragma once

#include <gmp.h>
#include <mpfr.h>

#include <variant>
#include <memory>
#include <optional>
#include <vector>
#include <iostream>

void copy_mpq(mpq_t dest, mpq_t src);
void copy_mpfr(mpfr_t dest, mpfr_t src);

typedef __mpfr_struct MPFloat;
typedef __mpq_struct MPRational;


enum NumType{
    NONE,
    FLOAT,
    RATIONAL
};

std::string to_rational_string(std::string s);

struct DynamicNum{ // can be real or rational
    void* nptr = nullptr;
    NumType type = NONE;

    inline size_t get_size(){return type == FLOAT ? sizeof(MPFloat) : sizeof(MPRational);}

    inline MPFloat* get_float(){return reinterpret_cast<MPFloat*>(nptr);}
    inline MPRational* get_rational(){return reinterpret_cast<MPRational*>(nptr);}

    inline void clear(){
        if (!nptr){
            return;
        }
        if (type == FLOAT){
            MPFloat* f = get_float();
            mpfr_clear(f);
        }
        else if (type == RATIONAL){
            MPRational* q = get_rational();
            mpq_clear(q);
        }
        free(nptr);
    }

    inline void set_float(MPFloat* f){
        clear();
        nptr = malloc(sizeof(MPFloat));
        memcpy(nptr, f, sizeof(MPFloat));
        type = FLOAT;
    }
    inline void set_rational(MPRational* q){
        clear();
        nptr = malloc(sizeof(MPRational));
        memcpy(nptr, q, sizeof(MPRational));
        type = RATIONAL;
    }

    void set(DynamicNum& src);

    void to_float();
    void to_rational();

    std::string get_str();

    DynamicNum deep_copy();

    DynamicNum(std::string str);

    DynamicNum();
};


struct DynamicVec{ // can store n-dimensional numbers
    std::vector<DynamicNum> dims;

    void print_long();
    void print_short();

    void set_dims(unsigned ndinms);

    void set_dim(DynamicNum& n, unsigned dim);

    DynamicVec(std::string str, unsigned dim);

    DynamicVec(DynamicNum& n, unsigned dim);

    DynamicVec() = default;

    ~DynamicVec();
};