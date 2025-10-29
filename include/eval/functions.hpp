#pragma once

#include <array>
#include <functional>
#include <string>

#include "trig.hpp"

// use X-macros to define math primitives

#define TRIG_FUNCTIONS                              \
    X(SIN, "sin", TrigFunctions::tok_sin, "sin(z)") \
    X(COS, "cos", TrigFunctions::tok_cos, "cos(z)") \
    X(TAN, "tan", TrigFunctions::tok_tan, "tan(z)") \
    X(SEC, "sec", TrigFunctions::tok_sec, "sec(z)") \
    X(COT, "cot", TrigFunctions::tok_cot, "cot(z)") \
    X(CSC, "csc", TrigFunctions::tok_csc, "csc(z)")

#define INV_TRIG_FUNCTIONS                              \
    X(ASIN, "asin", TrigFunctions::tok_asin, "asin(z)") \
    X(ACOS, "acos", TrigFunctions::tok_acos, "acos(z)") \
    X(ATAN, "atan", TrigFunctions::tok_atan, "atan(z)") \
    X(ASEC, "asec", TrigFunctions::tok_asec, "asec(z)") \
    X(ACOT, "acot", TrigFunctions::tok_acot, "acot(z)") \
    X(ACSC, "acsc", TrigFunctions::tok_acsc, "acsc(z)")

#define HYP_TRIG_FUNCTIONS                              \
    X(SINH, "sinh", TrigFunctions::tok_sinh, "sinh(z)") \
    X(COSH, "cosh", TrigFunctions::tok_cosh, "cosh(z)") \
    X(TANH, "tanh", TrigFunctions::tok_tanh, "tanh(z)") \
    X(SECH, "sech", TrigFunctions::tok_sech, "sech(z)") \
    X(COTH, "coth", TrigFunctions::tok_coth, "coth(z)") \
    X(CSCH, "csch", TrigFunctions::tok_csch, "csch(z)")

#define HYP_INV_TRIG_FUNCTIONS                              \
    X(ASINH, "asinh", TrigFunctions::tok_asinh, "asinh(z)") \
    X(ACOSH, "acosh", TrigFunctions::tok_acosh, "acosh(z)") \
    X(ATANH, "atanh", TrigFunctions::tok_atanh, "atanh(z)") \
    X(ASECH, "asech", TrigFunctions::tok_asech, "asech(z)") \
    X(ACOTH, "acoth", TrigFunctions::tok_acoth, "acoth(z)") \
    X(ACSCH, "acsch", TrigFunctions::tok_acsch, "acsch(z)")

#define LOG_FUNCTIONS                                              \
    X(LOG2, "log2", TrigFunctions::tok_sin, "log2(z)")             \
    X(LOG10, "log10", TrigFunctions::tok_sin, "log10(z)")          \
    X(LOG, "log", TrigFunctions::tok_sin, "log(z base, z result)") \
    X(LN, "ln", TrigFunctions::tok_sin, "ln(z)")

#define ROOT_FUNCTIONS /*...*/

#define EXP_FUNCTIONS /*...*/

#define CONSTANTS                                        \
    X(PI, "pi", TrigFunctions::tok_sin, "pi = ~3.14159") \
    X(E, "e", TrigFunctions::tok_sin, "e = ~2.71")       \
    X(PHI, "phi", TrigFunctions::tok_sin, "phi = ka")    \
    X(Y, "y", TrigFunctions::tok_sin, "y = ka2")

#define FUNCTIONS_MACRO    \
    HYP_INV_TRIG_FUNCTIONS \
    HYP_TRIG_FUNCTIONS     \
    INV_TRIG_FUNCTIONS     \
    TRIG_FUNCTIONS         \
    LOG_FUNCTIONS          \
    ROOT_FUNCTIONS         \
    EXP_FUNCTIONS

#define MATH_PRIMITIVES_MACRO \
    FUNCTIONS_MACRO           \
    CONSTANTS

enum class MathPrimitiveType { FUNCTION, CONSTANT };

enum class MathPrimitive {
#define X(a, b, c, d) a,
    MATH_PRIMITIVES_MACRO
#undef X
        COUNT
};

inline const std::array<std::string, (size_t)MathPrimitive::COUNT> MATH_PRIMITIVE_STRINGS = {
#define X(a, b, c, d) b,
    MATH_PRIMITIVES_MACRO

#undef X
};

inline const std::array<std::function<TokenPtrVec(Args&)>, (size_t)MathPrimitive::COUNT> MATH_PRIMITIVE_FUNCS = {
#define X(a, b, c, d) c,
    MATH_PRIMITIVES_MACRO
#undef X
};

inline const std::array<std::string, (size_t)MathPrimitive::COUNT> MATH_PRIMITVE_INFOS = {
#define X(a, b, c, d) d,
    MATH_PRIMITIVES_MACRO
#undef X
};

constexpr size_t CONSTANT_COUNT =
#define X(a, b, c, d) 1 +
    CONSTANTS
#undef X
    0;

constexpr size_t TOTAL_COUNT = static_cast<size_t>(MathPrimitive::COUNT);
constexpr size_t FUNCTION_COUNT = TOTAL_COUNT - CONSTANT_COUNT;

constexpr MathPrimitiveType get_math_primitive_type(MathPrimitive math_primitive_index) {
    if (static_cast<size_t>(math_primitive_index) < FUNCTION_COUNT) {
        return MathPrimitiveType::FUNCTION;
    }
    else if (static_cast<size_t>(math_primitive_index) < TOTAL_COUNT) {
        return MathPrimitiveType::CONSTANT;
    }
    return static_cast<MathPrimitiveType>(0);
}
