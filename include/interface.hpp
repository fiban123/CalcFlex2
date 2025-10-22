#pragma once 

#include "token_types.hpp"
#include "eval_config.hpp"

struct Result{
    TokenPtrVec tokens;

    std::string get_string();
};

inline void set_scientific_mode(bool sci){
    eval_config.out_representation_format = sci ? REPRESENTATION_FORMAT_SCI : REPRESENTATION_FORMAT_NORMAL;
}

inline void set_float_mode(bool f){
    eval_config.out_representation_type = f ? REPRESENTATION_TYPE_FLOAT : REPRESENTATION_TYPE_EXACT;
}

inline bool get_scientific_mode(){
    return eval_config.out_representation_format == REPRESENTATION_FORMAT_SCI;
}

inline bool get_float_mode(){
    return eval_config.out_representation_type == REPRESENTATION_TYPE_FLOAT;
}

typedef Result Result;