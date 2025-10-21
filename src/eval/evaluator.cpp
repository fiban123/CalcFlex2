#include "evaluator.hpp"
#include "flat_evaluator.hpp"
#include "tokenizer.hpp"


#include <iostream>
#include <sstream>
#include <algorithm> 

std::string tokenptrvec_to_string(TokenPtrVec& tokens){
}

std::string evaluate_string(std::string out){
    // remove whitespaces
    out.erase(std::remove(out.begin(), out.end(), ' '), out.end());

    TokenPtrVec tokens = tokenize(out);
    evaluate_flat_expression(tokens);

    std::cout << debug_tokens_to_string(tokens);
    std::cout << tokens_to_string(tokens);


    return tokens_to_string(tokens);
}