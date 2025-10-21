#include "evaluate_tokens.hpp"

#include "bracket_parser.hpp"
#include "flat_evaluator.hpp"
#include "primitive_evaluator.hpp"

void evaluate_tokens(TokenPtrVec& tokens){

    std::cout << "eval call " << debug_tokens_to_string(tokens) << std::endl;
    // recursively evaluate brackets

    for (size_t i = 0; i < tokens.size(); i++){
        Token* t = tokens[i].get();

        if (t->token_type == TokenType::BRACKET){
            BracketToken* bt = dynamic_cast<BracketToken*>(t);

            if (bt->type == BRACKET_OPENING){
                size_t opening = i;
                size_t closing = find_closing_bracket(tokens, opening);

                // move tokens inside brackets into another vector
                TokenPtrVec inside_brackets(
                    std::make_move_iterator(tokens.begin() + opening + 1),
                    std::make_move_iterator(tokens.begin() + closing)
                );

                // remove deleted tokens and brackets
                tokens.erase(tokens.begin() + opening, tokens.begin() + closing + 1);

                evaluate_tokens(inside_brackets);;;;;

                // replace opening bracket with result of evaluation
                tokens.insert(tokens.begin() + opening, 
                    std::make_move_iterator(inside_brackets.begin()), 
                    std::make_move_iterator(inside_brackets.end())
                );
            }
        }
    }

    evaluate_funcs(tokens);
    
    evaluate_flat_expression(tokens);
}