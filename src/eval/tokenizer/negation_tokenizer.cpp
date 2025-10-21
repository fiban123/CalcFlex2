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
                    // check if previous token is also an operator
                    if (i == 0){
                        create_negation_token(tokens, i);
                    }
                    else if (tokens[i - 1]->token_type == TokenType::OPERATOR || tokens[i - 1]->token_type == TokenType::NEGATION){
                        create_negation_token(tokens, i);
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