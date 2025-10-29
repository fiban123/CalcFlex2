#include <dynamic_vec_math.hpp>

#include "eval_config.hpp"

__attribute__((always_inline)) inline DynamicNum perform_operation(DynamicNum& l, DynamicNum& r, Operation op) {
    DynamicNum result;
    if (l.type == FLOAT && r.type == FLOAT) {
        // both are float
        MPFloat fresult;
        mpfr_init2(&fresult, eval_config.math_prec);

        op.f_f(&fresult, l.get_float(), r.get_float(), MPFR_RNDN);

        result.set_float(&fresult);
    }
    else if (l.type == FLOAT) {
        // only left is float
        MPFloat fresult;
        mpfr_init2(&fresult, eval_config.math_prec);

        op.f_q(&fresult, l.get_float(), r.get_rational(), MPFR_RNDN);

        result.set_float(&fresult);
    }
    else if (r.type == FLOAT) {
        // only right is float
        MPFloat fresult;
        mpfr_init2(&fresult, eval_config.math_prec);

        l.to_float();

        op.f_f(&fresult, l.get_float(), r.get_float(), MPFR_RNDN);

        result.set_float(&fresult);
    }
    else {
        // both are rational
        MPRational qresult;
        mpq_init(&qresult);

        op.q_q(&qresult, l.get_rational(), r.get_rational());
        mpq_canonicalize(&qresult);

        result.set_rational(&qresult);
    }

    return result;
}

DynamicNum operator+(DynamicNum& l, DynamicNum& r) { return perform_operation(l, r, op_add); }

DynamicNum operator-(DynamicNum& l, DynamicNum& r) { return perform_operation(l, r, op_sub); }

DynamicNum operator*(DynamicNum& l, DynamicNum& r) { return perform_operation(l, r, op_mul); }

DynamicNum operator/(DynamicNum& l, DynamicNum& r) {
    std::cout << "shduhd\n";
    if (r.type == RATIONAL) {
        std::cout << "ffshduhd\n";
        std::cout << mpz_cmp_ui(mpq_numref(r.get_rational()), 0) << "\n";
        std::cout << r.get_str(eval_config) << "\n";
        std::cout << "\naaa\n";
        if (mpz_cmp_ui(mpq_numref(r.get_rational()), 0) == 0) {
            r.to_float();
        }
    }
    return perform_operation(l, r, op_div);
}

DynamicVecPtr operator+(DynamicVec& lvec, DynamicVec& rvec) {
    DynamicVecPtr result;
    if (lvec.dims.size() == 1 && rvec.dims.size() == 1) {
        // both arent complex

        DynamicNum rresult = lvec.dims[0] + rvec.dims[0];

        result = std::make_unique<DynamicVec>(rresult, 0);
    }

    return result;
}

DynamicVecPtr operator-(DynamicVec& lvec, DynamicVec& rvec) {
    DynamicVecPtr result;
    if (lvec.dims.size() == 1 && rvec.dims.size() == 1) {
        // both arent complex

        DynamicNum rresult = lvec.dims[0] - rvec.dims[0];

        result = std::make_unique<DynamicVec>(rresult, 0);
    }

    return result;
}

DynamicVecPtr operator*(DynamicVec& lvec, DynamicVec& rvec) {
    DynamicVecPtr result;
    if (lvec.dims.size() == 1 && rvec.dims.size() == 1) {
        // both arent complex

        DynamicNum rresult = lvec.dims[0] * rvec.dims[0];

        result = std::make_unique<DynamicVec>(rresult, 0);
    }

    return result;
}

DynamicVecPtr operator/(DynamicVec& lvec, DynamicVec& rvec) {
    DynamicVecPtr result;
    if (lvec.dims.size() == 1 && rvec.dims.size() == 1) {
        // both arent complex

        DynamicNum rresult = lvec.dims[0] / rvec.dims[0];

        result = std::make_unique<DynamicVec>(rresult, 0);
    }

    return result;
}
