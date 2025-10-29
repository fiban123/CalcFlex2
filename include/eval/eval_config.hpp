#pragma once

#include <mpfr.h>

#include <iostream>

enum NumberRepresentationType {
    REPRESENTATION_TYPE_EXACT,
    REPRESENTATION_TYPE_FLOAT,
};

enum NumberRepresentationFormat { REPRESENTATION_FORMAT_NORMAL, REPRESENTATION_FORMAT_SCI };

struct EvalConfig {
    NumberRepresentationType out_representation_type;
    NumberRepresentationFormat out_representation_format;

    size_t sci_representation_n_digits;
    size_t auto_sci_threshold_n_digits;
    size_t sci_min_n_digits;
    bool auto_sci;

    size_t math_prec;
    size_t representation_prec;
};

inline EvalConfig eval_config{
    REPRESENTATION_TYPE_EXACT,
    REPRESENTATION_FORMAT_SCI,

    12,
    70,
    3,
    true,

    8192,
    128,
};

inline EvalConfig debug_eval_config{
    REPRESENTATION_TYPE_EXACT,
    REPRESENTATION_FORMAT_SCI,

    12,
    70,
    3,
    true,

    8192,
    128,
};
