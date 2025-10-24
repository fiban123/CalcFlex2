#pragma once

#include "trig.hpp"


#include <array>
#include <string>
#include <functional>


// use X-macros to define math primitives

#define TRIG_FUNCTIONS \
        X(SIN, "sin", TrigFunctions::tok_sin) \
        X(COS, "cos", TrigFunctions::tok_cos) \
        X(TAN, "tan", TrigFunctions::tok_tan) \
        X(SEC, "sec", TrigFunctions::tok_sec) \
        X(COT, "cot", TrigFunctions::tok_cot) \
        X(CSC, "csc", TrigFunctions::tok_csc) \

#define INV_TRIG_FUNCTIONS \
        X(ASIN, "asin", TrigFunctions::tok_asin) \
        X(ACOS, "acos", TrigFunctions::tok_acos) \
        X(ATAN, "atan", TrigFunctions::tok_atan) \
        X(ASEC, "asec", TrigFunctions::tok_asec) \
        X(ACOT, "acot", TrigFunctions::tok_acot) \
        X(ACSC, "acsc", TrigFunctions::tok_acsc) \

#define HYP_TRIG_FUNCTIONS \
        X(SINH, "sinh", TrigFunctions::tok_sinh) \
        X(COSH, "cosh", TrigFunctions::tok_cosh) \
        X(TANH, "tanh", TrigFunctions::tok_tanh) \
        X(SECH, "sech", TrigFunctions::tok_sech) \
        X(COTH, "coth", TrigFunctions::tok_coth) \
        X(CSCH, "csch", TrigFunctions::tok_csch) \

#define HYP_INV_TRIG_FUNCTIONS \
        X(ASINH, "asinh", TrigFunctions::tok_asinh) \
        X(ACOSH, "acosh", TrigFunctions::tok_acosh) \
        X(ATANH, "atanh", TrigFunctions::tok_atanh) \
        X(ASECH, "asech", TrigFunctions::tok_asech) \
        X(ACOTH, "acoth", TrigFunctions::tok_acoth) \
        X(ACSCH, "acsch", TrigFunctions::tok_acsch) \

#define LOG_FUNCTIONS \
        X(LOG2, "log2", TrigFunctions::tok_sin) \
        X(LOG10, "log10", TrigFunctions::tok_sin) \
        X(LOG, "log", TrigFunctions::tok_sin) \
        X(LN, "ln", TrigFunctions::tok_sin)

#define ROOT_FUNCTIONS /*...*/

#define EXP_FUNCTIONS /*...*/



#define CONSTANTS \
        X(PI, "pi", TrigFunctions::tok_sin) \
        X(E, "e", TrigFunctions::tok_sin) \
        X(PHI, "phi", TrigFunctions::tok_sin) \
        X(Y, "y", TrigFunctions::tok_sin)



#define FUNCTIONS_MACRO \
        HYP_INV_TRIG_FUNCTIONS \
        HYP_TRIG_FUNCTIONS \
        INV_TRIG_FUNCTIONS \
        TRIG_FUNCTIONS \
        LOG_FUNCTIONS \
        ROOT_FUNCTIONS \
        EXP_FUNCTIONS \

#define MATH_PRIMITIVES_MACRO \
        FUNCTIONS_MACRO \
        CONSTANTS

enum class MathPrimitiveType{
    FUNCTION,
    CONSTANT
};

enum class MathPrimitive{
    #define X(a, b, c) a,
    MATH_PRIMITIVES_MACRO
    #undef X
    COUNT
};


inline const std::array<std::string, (size_t) MathPrimitive::COUNT> MATH_PRIMITIVE_STRINGS = {
    #define X(a, b, c) b,
    MATH_PRIMITIVES_MACRO
    #undef X
};

inline const std::array<std::function<TokenPtrVec(Args&)>, (size_t) MathPrimitive::COUNT> MATH_PRIMITIVE_FUNCS = {
    #define X(a, b, c) c,
    MATH_PRIMITIVES_MACRO
    #undef X
};

constexpr size_t CONSTANT_COUNT = 
#define X(a, b, c) 1+
    CONSTANTS
#undef X
0;

constexpr size_t TOTAL_COUNT = static_cast<size_t>(MathPrimitive::COUNT);
constexpr size_t FUNCTION_COUNT = TOTAL_COUNT - CONSTANT_COUNT;

constexpr MathPrimitiveType get_math_primitive_type(MathPrimitive math_primitive_index){
    if (static_cast<size_t>(math_primitive_index) < FUNCTION_COUNT) {
        return MathPrimitiveType::FUNCTION;
    } 
    else if (static_cast<size_t>(math_primitive_index) < TOTAL_COUNT) {
        return MathPrimitiveType::CONSTANT;
    }
    return static_cast<MathPrimitiveType>(0);
}