#include "primitive_tokenizer.hpp"
#include "functions.hpp"

void create_primitive_token(TokenPtrVec& tokens, size_t token_pos, std::string& string, size_t string_pos, MathPrimitive p, size_t& i){
    unsigned op_len = MATH_PRIMITIVES[static_cast<size_t>(p)].length();

    std::cout << "sdsdsd" << MATH_PRIMITIVES[static_cast<size_t>(p)] << std::endl;

    // split string token into left and right part
    std::string left(string.begin(), string.begin() + string_pos);
    std::string right(string.begin() + string_pos + op_len, string.end());

    std::unique_ptr<Token> token;

    MathPrimitiveType p_type = get_math_primitive_type(p);

    if (p_type == MathPrimitiveType::FUNCTION){
        token = std::make_unique<FunctionToken>(p);
    }
    else{
        token = std::make_unique<ConstantToken>(p);;
    }

    emplace_token(tokens, token_pos, std::move(token), left, right, i);
}

size_t find_primitive(std::string& s, MathPrimitive& func_type){
    for (size_t i = 0; i < MATH_PRIMITIVES.size(); i++){
        size_t index = s.find(MATH_PRIMITIVES[i]);
        if (index != std::string::npos){
            func_type = static_cast<MathPrimitive>(i);
            return index;
        }
    }
    return std::string::npos;
}

void tokenize_primitive(TokenPtrVec &tokens){
    for (size_t i = 0; i < tokens.size(); i++){
        Token* t = tokens[i].get();

        if (t->token_type == TokenType::STRING){
            StringToken* st = dynamic_cast<StringToken*>(t);

            MathPrimitive p;

            size_t start = 0;
            size_t j = find_primitive(st->string, p);

            if (j != std::string::npos){
                create_primitive_token(tokens, i, st->string, j, p, i);
                i--;
            }
        }
    }
}