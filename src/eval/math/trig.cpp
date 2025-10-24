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

int mpfr_asec(mpfr_ptr out, mpfr_srcptr num, mpfr_rnd_t rnd){
    mpfr_ui_div(out, 1, num, rnd);
    mpfr_acos(out, out, rnd);

    return 0;
}
int mpfr_acot(mpfr_ptr out, mpfr_srcptr num, mpfr_rnd_t rnd){
    mpfr_ui_div(out, 1, num, rnd);
    mpfr_atan(out, out, rnd);

    return 0;
}
int mpfr_acsc(mpfr_ptr out, mpfr_srcptr num, mpfr_rnd_t rnd){
    mpfr_ui_div(out, 1, num, rnd);
    mpfr_asin(out, out, rnd);

    return 0;
}


int mpfr_asech(mpfr_ptr out, mpfr_srcptr num, mpfr_rnd_t rnd){
    mpfr_ui_div(out, 1, num, rnd);
    mpfr_acosh(out, out, rnd);

    return 0;
}
int mpfr_acoth(mpfr_ptr out, mpfr_srcptr num, mpfr_rnd_t rnd){
    mpfr_ui_div(out, 1, num, rnd);
    mpfr_atanh(out, out, rnd);

    return 0;
}
int mpfr_acsch(mpfr_ptr out, mpfr_srcptr num, mpfr_rnd_t rnd){
    mpfr_ui_div(out, 1, num, rnd);
    mpfr_sinh(out, out, rnd);

    return 0;
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


TokenPtrVec TrigFunctions::tok_asin(Args& args) {
    return call_basic_mpfr(mpfr_asin, args);
}
TokenPtrVec TrigFunctions::tok_acos(Args& args) {
    return call_basic_mpfr(mpfr_acos, args);
}
TokenPtrVec TrigFunctions::tok_atan(Args& args) {
    return call_basic_mpfr(mpfr_atan, args);
}
TokenPtrVec TrigFunctions::tok_asec(Args& args) {
    return call_basic_mpfr(mpfr_asec, args);
}
TokenPtrVec TrigFunctions::tok_acot(Args& args) {
    return call_basic_mpfr(mpfr_acot, args);
}
TokenPtrVec TrigFunctions::tok_acsc(Args& args) {
    return call_basic_mpfr(mpfr_acsc, args);
}


TokenPtrVec TrigFunctions::tok_sinh(Args& args) {
    return call_basic_mpfr(mpfr_sinh, args);
}
TokenPtrVec TrigFunctions::tok_cosh(Args& args) {
    return call_basic_mpfr(mpfr_cosh, args);
}
TokenPtrVec TrigFunctions::tok_tanh(Args& args) {
    return call_basic_mpfr(mpfr_tanh, args);
}
TokenPtrVec TrigFunctions::tok_sech(Args& args) {
    return call_basic_mpfr(mpfr_sech, args);
}
TokenPtrVec TrigFunctions::tok_coth(Args& args) {
    return call_basic_mpfr(mpfr_coth, args);
}
TokenPtrVec TrigFunctions::tok_csch(Args& args) {
    return call_basic_mpfr(mpfr_csch, args);
}


TokenPtrVec TrigFunctions::tok_asinh(Args& args) {
    return call_basic_mpfr(mpfr_asinh, args);
}

TokenPtrVec TrigFunctions::tok_acosh(Args& args) {
    return call_basic_mpfr(mpfr_acosh, args);
}

TokenPtrVec TrigFunctions::tok_atanh(Args& args) {
    return call_basic_mpfr(mpfr_atanh, args);
}

TokenPtrVec TrigFunctions::tok_asech(Args& args) {
    return call_basic_mpfr(mpfr_asech, args);
}

TokenPtrVec TrigFunctions::tok_acoth(Args& args) {
    return call_basic_mpfr(mpfr_acoth, args);
}

TokenPtrVec TrigFunctions::tok_acsch(Args& args) {
    return call_basic_mpfr(mpfr_acsch, args);
}
