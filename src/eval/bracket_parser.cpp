#include "bracket_parser.hpp"

template<typename TokenT, TokenType TokenTypeValue, auto OpeningValue, auto ClosingValue>
size_t arb_find_closing_bracket(TokenPtrVec& tokens, size_t i){
    size_t num_opening_brackets = 0;
    size_t num_closing_brackets = 0;

    for (size_t j = i; j < tokens.size(); j++){

        Token* t = tokens[j].get();
        if (t->token_type == TokenTypeValue){
            TokenT* bt = dynamic_cast<TokenT*>(t);
            if (bt->type == OpeningValue){
                num_opening_brackets++;
            }
            else if (bt->type == ClosingValue){
                num_closing_brackets++;
            }
        }

        if (num_closing_brackets != 0 && num_opening_brackets == num_closing_brackets){
            return j;
        }
    }

    return SIZE_MAX;
}

size_t find_closing_bracket(TokenPtrVec& tokens, size_t i) {
    return arb_find_closing_bracket<BracketToken, 
                                    TokenType::BRACKET,
                                    BRACKET_OPENING,
                                    BRACKET_CLOSING>(tokens, i);
}

size_t find_closing_function_bracket(TokenPtrVec& tokens, size_t i) {
    return arb_find_closing_bracket<FunctionBracketToken, 
                                    TokenType::FUNCTION_BRACKET,
                                    FUNCTION_BRACKET_OPENING,
                                    FUNCTION_BRACKET_CLOSING>(tokens, i);
}