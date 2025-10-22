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
}