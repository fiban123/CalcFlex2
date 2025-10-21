#include "primitive_evaluator.hpp"

#include "bracket_parser.hpp"
#include "evaluate_tokens.hpp"

void evaluate_funcs(TokenPtrVec& tokens){
    for (size_t i = 0; i < tokens.size() - 1; i++){
        Token* t = tokens[i].get();

        if (t->token_type == TokenType::FUNCTION){
            if (tokens[i + 1]->token_type == TokenType::FUNCTION_BRACKET){
                size_t opening = i + 1;
                size_t closing = find_closing_function_bracket(tokens, opening);

                std::vector<TokenPtrVec> args;

                TokenPtrVec inside_brackets(
                    std::make_move_iterator(tokens.begin() + opening + 1),
                    std::make_move_iterator(tokens.begin() + closing)
                );

                // evaluate whats inside brackets
                evaluate_tokens(inside_brackets);
                
                // split into args seperated by delimeters
                size_t start = 0;

                for (size_t j = 0; j < inside_brackets.size(); j++){
                    Token* ib_t = inside_brackets[j].get();

                    if (ib_t->token_type == TokenType::SEPARATOR){
                        // insert into args
                        args.emplace_back(
                            std::make_move_iterator(inside_brackets.begin() + start),
                            std::make_move_iterator(inside_brackets.begin() + j)
                        );
                        start = j + 1;
                    }
                }
                args.emplace_back(
                    std::make_move_iterator(inside_brackets.begin() + start),
                    std::make_move_iterator(inside_brackets.end())
                );
                // remove whats inside brackets and surrounding brackets and function
                tokens.erase(tokens.begin() + opening - 1, tokens.begin() + closing + 1);

                TokenPtrVec result;
                result.emplace_back(std::make_unique<NumberToken>(std::make_unique<DynamicVec>("89", 0)));

                // insert result
                tokens.insert(tokens.begin() + opening - 1, 
                                std::make_move_iterator(result.begin()),
                                std::make_move_iterator(result.end())
                );

                std::cout << "ARGS:" << std::endl;
                for (TokenPtrVec& arg : args){
                    std::cout << debug_tokens_to_string(arg) << std::endl;
                }
                std::cout << "llll" << std::endl;
            }
        }
    }
}

void evaluate_constants(TokenPtrVec& tokens){
}

void evaluate_primitives(TokenPtrVec& tokens){

}