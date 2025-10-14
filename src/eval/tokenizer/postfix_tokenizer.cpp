#include "postfix_tokenizer.hpp"
#include "functions.hpp"

void create_postfix_operator_token(TokenPtrVec& tokens, size_t token_pos, std::string& string, size_t string_pos, PostfixOperator pop, size_t& i){
    unsigned op_len = POSTFIX_OPERATORS[static_cast<size_t>(pop)].length();

    //std::cout << op_len << std::endl;
    //std::cout << string.length() << std::endl;
    //std::cout << string_pos << std::endl;
    //std::cout << (size_t) p << "asdsd\n";
    //std::cout << string  << "asdsd\n";


    // split string token into left and right part
    std::string left(string.begin(), string.begin() + string_pos);
    std::string right(string.begin() + string_pos + op_len, string.end());

    std::unique_ptr<PostfixOperatorToken> pop_token = std::make_unique<PostfixOperatorToken>(pop);

    emplace_token(tokens, token_pos, std::move(pop_token), left, right, i);
}

size_t find_postfix_operator(std::string& s, PostfixOperator& func_type){
    for (size_t i = 0; i < POSTFIX_OPERATORS.size(); i++){
        size_t index = s.find(POSTFIX_OPERATORS[i]);
        if (index != std::string::npos){
            func_type = static_cast<PostfixOperator>(i);
            std::cout << POSTFIX_OPERATORS[i] << "asdsd\n";
            std::cout << i << "asdsd\n";
            return index;
        }
    }
    return std::string::npos;
}

void tokenize_postfix_operator(TokenPtrVec &tokens){
    for (size_t i = 0; i < tokens.size(); i++){
        Token* t = tokens[i].get();

        if (t->token_type == TokenType::STRING){
            StringToken* st = dynamic_cast<StringToken*>(t);

            PostfixOperator pop;

            size_t start = 0;
            size_t j = find_postfix_operator(st->string, pop);


            if (j == 0){
                create_postfix_operator_token(tokens, i, st->string, 0, pop, i);
            }
        }

        else if (t->token_type == TokenType::OPERATOR){
            // check if next token is also an operator
            if (i == tokens.size() - 1){
                continue;
            }
            if (tokens[i + 1]->token_type == TokenType::OPERATOR){
                // check if it is a colliding postfix operator
            }
        }
    }
}