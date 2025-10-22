#pragma once

#include <vector>
#include <memory>

enum class TokenType{
    NONE,
    NUMBER,
    BRACKET,
    OPERATOR,
    NEGATION,
    FUNCTION,
    CONSTANT,
    POSTFIX_OPERATOR,
    FUNCTION_BRACKET,
    SEPARATOR,
    STRING
};

struct Token{
    TokenType token_type = TokenType::NONE;
    virtual ~Token() = default;
    Token() = default;
};

typedef std::vector<std::unique_ptr<Token> > TokenPtrVec;
typedef std::unique_ptr<Token> TokenPtr;
typedef std::vector<TokenPtrVec> Args;