#include "negation_tokenizer.hpp"

void create_negation_token(TokenPtrVec& tokens, size_t token_pos){
    tokens[token_pos] = std::make_unique<NegationToken>();
}

void tokenize_negation(TokenPtrVec &tokens){
    for (size_t i = 0; i < tokens.size(); i++){
        Token* t = tokens[i].get();

        if (t->token_type == TokenType::OPERATOR){
            {
                OperatorToken* ot = dynamic_cast<OperatorToken*>(t);

                if (ot->op == NEGATION_OPERATOR){
                    // check if previous token is also an operator or an opening bracket
                    if (i != 0){
                        std::cout <<"c" << (size_t) tokens[i - 1]->token_type << std::endl;
                    }
                    if (i == 0){
                        create_negation_token(tokens, i);
                    }
                    else if (
                        tokens[i - 1]->token_type == TokenType::OPERATOR || 
                        tokens[i - 1]->token_type == TokenType::NEGATION){
                        std::cout << "operator" << std::endl;
                        create_negation_token(tokens, i);
                    }
                    else if (tokens[i - 1]->token_type == TokenType::BRACKET){
                        std::cout << "bracket" << std::endl;
                        BracketToken* bt = dynamic_cast<BracketToken*>(tokens[i - 1].get());

                        if (bt->type == BRACKET_OPENING){
                            create_negation_token(tokens, i);
                        };
                    }
                    else if (tokens[i - 1]->token_type == TokenType::FUNCTION_BRACKET){
                        std::cout << "function bracket" << std::endl;
                        FunctionBracketToken* bt = dynamic_cast<FunctionBracketToken*>(tokens[i - 1].get());

                        if (bt->type == FUNCTION_BRACKET_OPENING){
                            create_negation_token(tokens, i);
                        }
                    }
                    else{
                        std::cout <<"cc" << (size_t) tokens[i - 1]->token_type << std::endl;
                    }

                }
            }
            
            // erase 2 consecutive negations
            if (i != 0){
                if (tokens[i]->token_type == TokenType::NEGATION && tokens[i - 1]->token_type == TokenType::NEGATION){
                    tokens.erase(tokens.begin() + i - 1, tokens.begin() + i + 1);
                    i -= 2;
                }
            }
        }
    }
}