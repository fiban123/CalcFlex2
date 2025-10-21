#include "bracket_parser.hpp"

bool is_opening_bracket(TokenPtrVec& tokens, size_t i){
    Token* t = tokens[i].get();
    if (t->token_type == TokenType::BRACKET){
        BracketToken* bt = dynamic_cast<BracketToken*>(t);
    }
    else if (t->token_type == TokenType::FUNCTION_BRACKET){
        BracketToken* bt = dynamic_cast<BracketToken*>(t);
    }
}

size_t find_closing_bracket(TokenPtrVec& tokens, size_t i) {
    size_t num_opening_brackets = 0;
    size_t num_closing_brackets = 0;

    for (size_t j = i; j < tokens.size(); j++){

        Token* t = tokens[j].get();
        if (t->token_type == TokenType::BRACKET){
            BracketToken* bt = dynamic_cast<BracketToken*>(t);
            if (bt->type == BRACKET_OPENING){
                num_opening_brackets++;
            }
            else{
                num_closing_brackets++;
            }
        }

        if (num_closing_brackets != 0 && num_opening_brackets == num_closing_brackets){
            return j;
        }
    }
}
