#pragma once

#include "tokenizer.hpp"
#include <functional>

TokenPtrVec call_mpfr(std::function<int(mpfr_ptr, mpfr_srcptr, mpfr_rnd_t)> mpfr_func, Args& args){
    if (args.size() == 1 && args[0].size() == 1 && args[0][0]->token_type == TokenType::NUMBER){
        NumberToken* num_tok = dynamic_cast<NumberToken*>(args[0][0].get());
        DynamicVec* num_vec = num_tok->n.get();
        if (num_tok->n->dims.size() == 1){
            DynamicNum& num = num_vec->dims[0];
            num.to_float();

            mpfr_func(num.get_float(), num.get_float(), MPFR_RNDN);

            TokenPtrVec out;
            out.emplace_back(std::make_unique<NumberToken>(std::move(num_vec)));
        }
    }
}

TokenPtrVec tok_sin(Args& args){
    mpfr_sin()
}