#pragma once

#include "dynamic_vec.hpp"

void f_factorial(mpfr_ptr f);

void pos_z_factorial(mpz_ptr z);

void num_factorial(DynamicNum& num);

void vec_factorial(DynamicVec& vec);