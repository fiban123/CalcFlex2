#pragma once

#include <array>
#include <string>

// use X-macros to define math primitives

#define TRIG_FUNCTIONS \
        X(SIN, "sin") \
        X(COS, "cos") \
        X(TAN, "tan") \

#define INV_TRIG_FUNCTIONS \
        X(ASIN, "asin") \
        X(ACOS, "acos") \
        X(ATAN, "atan") \

#define HYP_TRIG_FUNCTIONS /*...*/

#define HYP_INV_TRIG_FUNCTIONS /*...*/

#define LOG_FUNCTIONS \
        X(LOG2, "log2") \
        X(LOG10, "log10") \
        X(LOG, "log") \
        X(LN, "ln")

#define ROOT_FUNCTIONS /*...*/

#define EXP_FUNCTIONS /*...*/



#define CONSTANTS \
        X(PI, "pi") \
        X(E, "e") \
        X(PHI, "phi") \
        X(Y, "y")



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
    #define X(a, b) a,
    MATH_PRIMITIVES_MACRO
    #undef X
    COUNT
};


inline const std::array<std::string, (size_t) MathPrimitive::COUNT> MATH_PRIMITIVES = {
    #define X(a, b) b,
    MATH_PRIMITIVES_MACRO
    #undef X
};

constexpr size_t CONSTANT_COUNT = 
#define X(a, b) 1+
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