#include "bracket_tokenizer.hpp"

void tokenize_brackets(TokenPtrVec& tokens, std::string& expression){
    size_t string_start = 0;

    for (size_t i = 0; i < expression.length(); i++){
        char c = expression[i];

        if (c == '(' || c == ')'){
            std::string str(expression.begin() + string_start, expression.begin() + i - 1);

            tokens.emplace_back(std::make_unique<StringToken>(str));

            if (c == '('){
                tokens.emplace_back(std::make_unique<BracketToken>(BRACKET_OPENING));
            }
            else if (c == ')'){
                tokens.emplace_back(std::make_unique<BracketToken>(BRACKET_CLOSING));
            }

            string_start = i + 1;
        }
    }
}