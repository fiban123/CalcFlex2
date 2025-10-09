#pragma once

#include "dynamic_vec.hpp"

MPFloat to_float(MPRational *src);

DynamicNum operator+(DynamicNum &l, DynamicNum &r);



DynamicVec operator+(DynamicVec &l, DynamicVec &r);

DynamicVec operator-(DynamicVec& l, DynamicVec& r);

DynamicVec operator*(DynamicVec& l, DynamicVec& r);

DynamicVec operator/(DynamicVec& l, DynamicVec& r);