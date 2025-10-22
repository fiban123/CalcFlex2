#include "bracket_tokenizer.hpp"

void tokenize_brackets(TokenPtrVec& tokens, std::string& expression){
    size_t string_start = 0;

    for (size_t i = 0; i < expression.length(); i++){
        char c = expression[i];

        if (c == '(' || c == ')'){
            if (string_start != i){
                std::string str(expression.begin() + string_start, expression.begin() + i);

                if (!str.empty()){
                    tokens.emplace_back(new StringToken(str));
                }
            }


            if (c == '('){
                tokens.emplace_back(std::make_unique<BracketToken>(BRACKET_OPENING));
            }
            else if (c == ')'){
                tokens.emplace_back(std::make_unique<BracketToken>(BRACKET_CLOSING));
            }

            string_start = i + 1;
        }
    }

    if (string_start != expression.length()){
        std::string str(expression.begin() + string_start, expression.end());
    
        tokens.emplace_back(std::make_unique<StringToken>(str));
    }

}