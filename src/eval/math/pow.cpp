#include "pow.hpp"

// convert both numbers to float and perform pow
DynamicNum float_pow(DynamicNum& base, DynamicNum& exponent) {
    DynamicNum result;

    DynamicNum base_float;
    DynamicNum exponent_float;

    DynamicNum* baseptr = &base;
    DynamicNum* exponentptr = &exponent;

    std::cout << base.get_str(eval_config) << std::endl;
    std::cout << exponent.get_str(eval_config) << std::endl;

    if (base.type == RATIONAL){
        base_float = to_float(base);
        baseptr = &base_float;
    }
    if (exponent.type == RATIONAL){
        exponent_float = to_float(exponent);
        exponentptr = &exponent_float;
    }

    mpfr_t fresult;
    mpfr_init2(fresult, eval_config.math_prec);
    // perform pow()
    mpfr_pow(fresult, baseptr->get_float(), exponentptr->get_float(), MPFR_RNDN);

    result.set_float(fresult);


    base_float.clear();
    exponent_float.clear();

    return result;
}

void mpz_pow_z(mpz_ptr out, mpz_srcptr base, mpz_srcptr exponent){
    // fast exponentiation
    mpz_t e, b;
    mpz_init_set(e, exponent);
    mpz_init_set(b, base);
    mpz_set_ui(out, 1);

    while (mpz_sgn(e) > 0) {
        // if e is odd
        if (mpz_odd_p(e)) {
            mpz_mul(out, out, b);
        }
        // b = b * b
        mpz_mul(b, b, b);     
        // e = e / 2 
        mpz_fdiv_q_2exp(e, e, 1);
    }

    mpz_clear(e);
    mpz_clear(b);
}

void mpq_pow_z(mpq_ptr out, mpq_srcptr base, mpz_srcptr exponent){
    int cmp = mpz_cmp_ui(exponent, 0);
    int big_exponent = mpz_cmp_ui(exponent, 16);

    if (cmp > 0){
        // exponent is positive
        if (big_exponent > 0){
            // big exponent
            mpz_pow_z(mpq_numref(out), mpq_numref(base), exponent);
            mpz_pow_z(mpq_denref(out), mpq_denref(base), exponent);
        }
        else{
            // small exponent
            mpz_pow_ui(mpq_numref(out), mpq_numref(base), mpz_get_ui(exponent));
            mpz_pow_ui(mpq_denref(out), mpq_denref(base), mpz_get_ui(exponent));
        }

    }
    else if (cmp == 0){
        // exponent is 0, set to 1/1
        mpq_set_ui(out, 1, 1);
    }
    else{
        mpz_t abs_exponent;
        mpz_init(abs_exponent);
        mpz_abs(abs_exponent, exponent);

        if (big_exponent > 0){
            // big exponent
            mpz_pow_z(mpq_numref(out), mpq_denref(base), abs_exponent);
            mpz_pow_z(mpq_denref(out), mpq_numref(base), abs_exponent);
        }
        else{
            // small exponent
            mpz_pow_ui(mpq_numref(out), mpq_numref(base), mpz_get_ui(abs_exponent));
            mpz_pow_ui(mpq_denref(out), mpq_denref(base), mpz_get_ui(abs_exponent));
        }
        mpz_clear(abs_exponent);
    }
}

DynamicNum z_pow(DynamicNum& base, mpz_t exponent){
    DynamicNum result;

    if (base.type == RATIONAL){
        mpq_t qresult;
        mpq_init(qresult);

        mpq_pow_z(qresult, base.get_rational(), exponent);

        mpq_canonicalize(qresult);

        result.set_rational(qresult);
    }

    else if (base.type == FLOAT){
        mpfr_t fresult;
        mpfr_init2(fresult, eval_config.math_prec);

        mpfr_pow_z(fresult, base.get_float(), exponent, MPFR_RNDN);

        result.set_float(fresult);
    }

    return result;
}

DynamicNum num_pow(DynamicNum& base, DynamicNum& exponent) {
    DynamicNum result;

    if (exponent.type == RATIONAL){
        // check if denominator of exponent is 1

        if (mpz_cmp_ui(mpq_denref(exponent.get_rational()), 1) == 0){
            // it is one
            result = z_pow(base, mpq_numref(exponent.get_rational()));
        }
        else{


            result = float_pow(base, exponent);
        }
    }
    else{
        result = float_pow(base, exponent);
    }

    return result;
}

DynamicVecPtr vec_pow(DynamicVec& base, DynamicVec& exponent) { 
    DynamicVecPtr result;
    if (base.dims.size() == 1 && exponent.dims.size() == 1){
        // both arent complex

        DynamicNum rresult = num_pow(base.dims[0], exponent.dims[0]);

        result = std::make_unique<DynamicVec>(rresult, 0);
    }
    return result;
}
