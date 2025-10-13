#pragma once

#include "dynamic_vec.hpp"

#include <functional>


typedef std::function<int(mpfr_ptr, mpfr_srcptr, mpfr_srcptr, mpfr_rnd_t)> f_f_operation;
typedef std::function<int(mpfr_ptr, mpfr_srcptr, mpq_srcptr, mpfr_rnd_t)> f_q_operation;
typedef std::function<void(mpq_ptr, mpq_srcptr, mpq_srcptr)> q_q_operation;

struct Operation{
    f_f_operation f_f; // both operands are float
    f_q_operation f_q; // one operand is float and one rational
    q_q_operation q_q; // both operands are rational
};

inline Operation op_add{mpfr_add, mpfr_add_q, mpq_add};
inline Operation op_sub{mpfr_sub, mpfr_sub_q, mpq_sub};

inline Operation op_mul{mpfr_mul, mpfr_mul_q, mpq_mul};
inline Operation op_div{mpfr_div, mpfr_div_q, mpq_div};



DynamicNum operator+(DynamicNum &l, DynamicNum &r);
DynamicNum operator-(DynamicNum &l, DynamicNum &r);

DynamicNum operator*(DynamicNum &l, DynamicNum &r);
DynamicNum operator/(DynamicNum &l, DynamicNum &r);


DynamicVecPtr operator+(DynamicVec &lvec, DynamicVec &rvec);
DynamicVecPtr operator-(DynamicVec &lvec, DynamicVec &rvec);

DynamicVecPtr operator*(DynamicVec &lvec, DynamicVec &rvec);
DynamicVecPtr operator/(DynamicVec &lvec, DynamicVec &rvec);