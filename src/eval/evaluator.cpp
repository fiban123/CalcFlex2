#include "evaluator.hpp"
#include "flat_evaluator.hpp"
#include "tokenizer.hpp"


#include <iostream>

std::string evaluate_string(std::string out){
    TokenPtrVec tokens = tokenize(out);
    print_tokenptrvec(tokens);
    evaluate_flat_expression(tokens);
    print_tokenptrvec(tokens);;


    return "69420";
}