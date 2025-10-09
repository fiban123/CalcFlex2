#include "tokenizer.hpp"

#include "bracket_tokenizer.hpp"
#include "operator_tokenizer.hpp"
#include "number_tokenizer.hpp"

#include <vector>

TokenPtrVec tokenize(std::string& expression){
    TokenPtrVec tokens;

    tokenize_brackets(tokens, expression);
    tokenize_operators(tokens);
    tokenize_numbers(tokens);

    return tokens;
}