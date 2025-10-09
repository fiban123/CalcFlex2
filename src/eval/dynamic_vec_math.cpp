#include <dynamic_vec_math.hpp>


DynamicNum operator+(DynamicNum &l, DynamicNum& r){
    DynamicNum result;
    if (l.type == FLOAT || r.type == FLOAT){
        // at least one of them is float
        MPFloat fresult;
        mpfr_init(&fresult);

        l.to_float();
        r.to_float();
        mpfr_add(&fresult, l.get_float(), r.get_float(), MPFR_RNDN);

        result.set_float(&fresult);
    }
    else{
        // add 2 rationals
        MPRational qresult;
        mpq_init(&qresult);

        mpq_add(&qresult, l.get_rational(), r.get_rational());

        result.set_rational(&qresult);;
    }

    return result;
}

DynamicVec operator+(DynamicVec &lvec, DynamicVec &rvec){
    DynamicVec result;
    if (lvec.dims.size() == 1 && rvec.dims.size() == 1){
        // both arent complex

        DynamicNum rresult = lvec.dims[0] + rvec.dims[0];

        result.set_dim(rresult, 0);
    }

    return result;
}

DynamicVec operator-(DynamicVec &l, DynamicVec &r)
{

}

DynamicVec operator*(DynamicVec &l, DynamicVec &r)
{

}

DynamicVec operator/(DynamicVec &l, DynamicVec &r)
{

}
