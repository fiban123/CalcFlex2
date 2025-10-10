#include "number_tokenizer.hpp"

void create_number_token(TokenPtrVec& tokens, StringToken* str_token, size_t string_i, size_t& token_i){
    size_t start = string_i;

    while (is_number(str_token->string[string_i])){
        string_i++;
    }

    std::string numstr(str_token->string.begin() + start, str_token->string.begin() + string_i);

    size_t numstr_len = numstr.length();

    std::unique_ptr<DynamicVec> num = std::make_unique<DynamicVec>(numstr, 0);
    std::unique_ptr<NumberToken> num_token = std::make_unique<NumberToken>(std::move(num));

    std::string left(str_token->string.begin(), str_token->string.begin() + start);
    std::string right(str_token->string.begin() + start + numstr_len, str_token->string.end());

    std::cout << left << numstr << right << "\n";


    emplace_token(tokens, token_i, std::move(num_token), left, right, token_i);
}

void tokenize_numbers(TokenPtrVec &tokens){
    for (size_t i = 0; i < tokens.size(); i++){
        Token* t = tokens[i].get();

        if (t->token_type == TokenType::STRING){
            StringToken* st = dynamic_cast<StringToken*>(t);

            for (size_t j = 0; j < st->string.length(); j++){
                if (is_number(st->string[j])){
                    create_number_token(tokens, st, j, i);
                    break;
                }
            }
        }
    }
}