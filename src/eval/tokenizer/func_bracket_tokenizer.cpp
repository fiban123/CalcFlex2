#include "func_bracket_tokenizer.hpp"

#include "bracket_parser.hpp"

void create_func_bracket_token(TokenPtrVec& tokens, size_t token_pos, FunctionBracketType type){
    tokens[token_pos] = std::make_unique<FunctionBracketToken>(type);
}

void tokenize_func_brackets(TokenPtrVec &tokens){
    for (size_t i = 1; i < tokens.size(); i++){
        Token* t = tokens[i].get();

        if (t->token_type == TokenType::BRACKET){
            // check if previous token is a function
            if (tokens[i - 1]->token_type == TokenType::FUNCTION){
                size_t opening_pos = i;
                size_t closing_pos = find_closing_bracket(tokens, opening_pos);

                create_func_bracket_token(tokens, opening_pos, FUNCTION_BRACKET_OPENING);
                create_func_bracket_token(tokens, closing_pos, FUNCTION_BRACKET_CLOSING);
            }
        }
    }
}