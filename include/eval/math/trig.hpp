#pragma once

#include "token_types.hpp"
#include "dynamic_vec.hpp"

#include <mpfr.h>

#include <functional>

namespace TrigFunctions{
    TokenPtrVec tok_sin(Args& args);
    TokenPtrVec tok_cos(Args& args);
    TokenPtrVec tok_tan(Args& args);
    TokenPtrVec tok_sec(Args& args);
    TokenPtrVec tok_cot(Args& args);
    TokenPtrVec tok_csc(Args& args);

    TokenPtrVec tok_asin(Args& args);
    TokenPtrVec tok_acos(Args& args);
    TokenPtrVec tok_atan(Args& args);
    TokenPtrVec tok_asec(Args& args);
    TokenPtrVec tok_acot(Args& args);
    TokenPtrVec tok_acsc(Args& args);

    TokenPtrVec tok_sinh(Args& args);
    TokenPtrVec tok_cosh(Args& args);
    TokenPtrVec tok_tanh(Args& args);
    TokenPtrVec tok_sech(Args& args);
    TokenPtrVec tok_coth(Args& args);
    TokenPtrVec tok_csch(Args& args);

    TokenPtrVec tok_asinh(Args& args);
    TokenPtrVec tok_acosh(Args& args);
    TokenPtrVec tok_atanh(Args& args);
    TokenPtrVec tok_asech(Args& args);
    TokenPtrVec tok_acoth(Args& args);
    TokenPtrVec tok_acsch(Args& args);
}