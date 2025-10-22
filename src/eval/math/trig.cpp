#include "trig.hpp"

#include "tokenizer.hpp"

// evaluates a token array that contains only a 1D number with a MPFR function and returns the result.
TokenPtrVec call_basic_mpfr(std::function<int(mpfr_ptr, mpfr_srcptr, mpfr_rnd_t)> mpfr_func, Args& args){
    std::cout << "  " << args.size()<< "  " << args[0].size()<< "  " << (size_t) args[0][0]->token_type;
    std::cout << debug_tokens_to_string(args[0]) << std::endl;

    if (args.size() == 1 && args[0].size() == 1 && args[0][0]->token_type == TokenType::NUMBER){
        NumberToken* num_tok = dynamic_cast<NumberToken*>(args[0][0].get());
        std::unique_ptr<DynamicVec> num_vec = std::move(num_tok->n);

        if (num_vec->dims.size() == 1){
            DynamicNum& num = num_vec->dims[0];;
            num.to_float();

            mpfr_func(num.get_float(), num.get_float(), MPFR_RNDN);

            TokenPtrVec out;
            out.emplace_back(std::make_unique<NumberToken>(std::move(num_vec)));
            return out;
        }
    }
}

TokenPtrVec TrigFunctions::tok_sin(Args& args) {
    return call_basic_mpfr(mpfr_sin, args);
}

TokenPtrVec TrigFunctions::tok_cos(Args& args) {
    return call_basic_mpfr(mpfr_cos, args);
}

TokenPtrVec TrigFunctions::tok_tan(Args& args) {
    return call_basic_mpfr(mpfr_tan, args);
}

TokenPtrVec TrigFunctions::tok_sec(Args& args) {
    return call_basic_mpfr(mpfr_sec, args);
}

TokenPtrVec TrigFunctions::tok_cot(Args& args) {
    return call_basic_mpfr(mpfr_cot, args);
}

TokenPtrVec TrigFunctions::tok_csc(Args& args) {
    return call_basic_mpfr(mpfr_csc, args);

}
