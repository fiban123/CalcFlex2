#include "separator_tokenizer.hpp"


void create_separator_token(TokenPtrVec& tokens, size_t token_pos, std::string& string, size_t string_pos, size_t& i){
    unsigned op_len = 1;

    // split string token into left and right part
    std::string left(string.begin(), string.begin() + string_pos);
    std::string right(string.begin() + string_pos + op_len, string.end());

    std::unique_ptr<SeparatorToken> sep_token = std::make_unique<SeparatorToken>();

    emplace_token(tokens, token_pos, std::move(sep_token), left, right, i);
}

void tokenize_separators(TokenPtrVec &tokens){
    for (size_t i = 0; i < tokens.size(); i++){
        Token* t = tokens[i].get();

        if (t->token_type == TokenType::STRING){
            StringToken* st = dynamic_cast<StringToken*>(t);

            size_t j = st->string.find(',');

            if (j != std::string::npos){
                create_separator_token(tokens, i, st->string, j, i);
            }
        }
    }
}