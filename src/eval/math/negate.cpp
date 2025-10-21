#include "negate.hpp"

void num_negate(DynamicNum& num) {
    if (num.type == FLOAT){
        mpfr_neg(num.get_float(), num.get_float(), MPFR_RNDN);
    }
    else if (num.type == RATIONAL){
        mpq_neg(num.get_rational(), num.get_rational());
    }
}

void vec_negate(DynamicVec& vec) {
    if (vec.dims.size() == 1){
        num_negate(vec.dims[0]);
    }
}
