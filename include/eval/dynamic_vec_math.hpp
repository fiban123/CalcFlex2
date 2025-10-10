#pragma once

#include "dynamic_vec.hpp"

DynamicNum operator+(DynamicNum &l, DynamicNum &r);

DynamicVecPtr operator+(DynamicVec &lvec, DynamicVec &rvec);


DynamicVec operator-(DynamicVec& l, DynamicVec& r);

DynamicVec operator*(DynamicVec& l, DynamicVec& r);

DynamicVec operator/(DynamicVec& l, DynamicVec& r);