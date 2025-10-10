#include "operator_tokenizer.hpp"

void create_operator_token(TokenPtrVec& tokens, size_t token_pos, std::string string, size_t string_pos, Operator op, size_t& i){
    // [str]1+1 -> [str]1, [op]+, [str]1

    unsigned op_len = std::string(OPERATORS[static_cast<size_t>(op)]).length();
    // split string token into left and right part
    std::string left(string.begin(), string.begin() + string_pos);

    std::string right(string.begin() + string_pos + op_len, string.end());

    std::unique_ptr<OperatorToken> op_token = std::make_unique<OperatorToken>(op);

    emplace_token(tokens, token_pos, std::move(op_token), left, right, i);
}

size_t find_operator(std::string& s, Operator& op_type){
    for (size_t i = 1; i < OPERATORS.size(); i++){
        size_t index = s.find_first_of(OPERATORS[i]);
        if (index != std::string::npos){
            op_type = static_cast<Operator>(i);
            return index;
        }
    }
    return std::string::npos;
}

void tokenize_operators(TokenPtrVec &tokens){
    std::cout << "sdsdsd" << "\n";
    for (size_t i = 0; i < tokens.size(); i++){
        Token* t = tokens[i].get();

        if (t->token_type == TokenType::STRING){
            StringToken* st = dynamic_cast<StringToken*>(t);

            Operator operator_type;

            size_t j = find_operator(st->string, operator_type);

            if (j != std::string::npos){
                create_operator_token(tokens, i, st->string, j, operator_type, i);
            }
        }
    }
}