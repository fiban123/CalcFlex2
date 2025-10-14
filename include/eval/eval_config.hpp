#pragma once

#include <iostream>

enum NumberRepresentationType{
    REPRESENTATION_TYPE_EXACT,
    REPRESENTATION_TYPE_FLOAT,
};

enum NumberRepresentationFormat{
    REPRESENTATION_FORMAT_NORMAL,
    REPRESENTATION_FORMAT_SCI
};

struct EvalConfig{
    NumberRepresentationType out_representation_type;
    NumberRepresentationFormat out_representation_format;
    size_t math_prec;
    size_t representation_prec;
    size_t sci_representation_n_digits;
};

inline EvalConfig eval_config{
    REPRESENTATION_TYPE_EXACT,
    REPRESENTATION_FORMAT_NORMAL,
    2048,
    1024,
    12,
};

inline EvalConfig debug_eval_config{
    REPRESENTATION_TYPE_EXACT, 
    REPRESENTATION_FORMAT_NORMAL,
    2048,
    1024,
    12,
};