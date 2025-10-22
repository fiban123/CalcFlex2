#include "factorial.hpp"

void f_factorial(mpfr_ptr f) {
    mpfr_t tmp;
    mpfr_init2(tmp, eval_config.math_prec);

    mpfr_add_ui(tmp, f, 1, MPFR_RNDN);  // tmp = f + 1
    mpfr_gamma(f, tmp, MPFR_RNDN);      // f = gamma(tmp)

    mpfr_clear(tmp);
}

void pos_z_factorial(mpz_ptr z){
    // handle 0 and 1
    if (mpz_cmp_ui(z, 0) == 0){
        mpz_set_ui(z, 1);
        return;
    }
    else if (mpz_cmp_ui(z, 1) == 0){
        mpz_set_ui(z, 1);
        return;
    }

    // initialize counter
    mpz_t i;
    mpz_init(i);
    mpz_set(i, z);

    mpz_set_ui(z, 1);

    unsigned long g = 0;

    while(mpz_cmp_ui(i, 1) > 0){
        mpz_mul(z, z, i); // z = z * i
        mpz_sub_ui(i, i, 1); // i--
        std::cout << g << std::endl;
        g++;
    }

    mpz_clear(i);
}

void num_factorial(DynamicNum& num){
    if (num.type == FLOAT){
        f_factorial(num.get_float());
    }
    else if (num.type == RATIONAL){
        MPRational* q = num.get_rational();

        // check if denominator is one and is positive
        if (mpq_is_den_one(q) && mpq_sgn(q) == 1){
            pos_z_factorial(mpq_numref(q));
        }
        else{
            // convert to float
            mpfr_t f;
            mpfr_init2(f, eval_config.math_prec);
            mpfr_set_q(f, q, MPFR_RNDN);

            f_factorial(f);

            num.set_float(f);
        }
    }
}

void vec_factorial(DynamicVec& vec){
    if (vec.dims.size() == 1){
        num_factorial(vec.dims[0]);
    }
}