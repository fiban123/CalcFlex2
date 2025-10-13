#pragma once

#include <dynamic_vec.hpp>
#include <dynamic_vec_math.hpp>

DynamicNum float_pow(DynamicNum& base, DynamicNum & exponent);

void mpz_pow_z(mpz_ptr out, mpz_src_ptr base, mpz_srcptr exponent);

DynamicNum num_pow(DynamicNum& base, DynamicNum& exponent);

DynamicVecPtr vec_pow(DynamicVec& base, DynamicVec& exponent);