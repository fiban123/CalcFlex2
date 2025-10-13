#pragma once

#include "dynamic_vec.hpp"


enum class TokenType{
    NONE,
    NUMBER,
    BRACKET,
    OPERATOR,
    FUNCTION,
    CONSTANT,
    FUNCTION_BRACKET,
    SEPARATOR,
    STRING
};

enum FunctionBracketType{
    FUNCTION_BRACKET_NONE,
    FUNCTION_BRACKET_OPENING,
    FUNCTION_BRACKET_CLOSING
};

enum BracketType{
    BRACKET_NONE,
    BRACKET_OPENING,
    BRACKET_CLOSING
};

enum Operator{
    OPERATOR_NONE,
    OPERATOR_ADD,
    OPERATOR_SUB,
    OPERATOR_MUL,
    OPERATOR_DIV
};

inline constexpr std::array<std::string_view, 5> OPERATORS = {"", "+", "-", "*", "/"};

enum class Constant{
    NONE,
    PI,
    E,
    PHI
};

struct Token{
    TokenType token_type = TokenType::NONE;
    virtual ~Token() = default;
    Token() = default;
};

struct NumberToken : Token{
    std::unique_ptr<DynamicVec> n;

    NumberToken(std::unique_ptr<DynamicVec> _n): n(std::move(_n)){token_type = TokenType::NUMBER;};
    NumberToken(){token_type = TokenType::NUMBER;}
};

struct BracketToken : Token{
    BracketType type;

    BracketToken(BracketType _type) : type(_type){token_type = TokenType::BRACKET;}
    BracketToken(){token_type = TokenType::BRACKET;}
};

struct OperatorToken : Token{
    Operator op;

    OperatorToken(Operator _op) : op(_op){token_type = TokenType::OPERATOR;};
    OperatorToken(){token_type = TokenType::OPERATOR;}
};

struct FunctionToken : Token{
    std::string name;

    FunctionToken(std::string _name) : name(_name){token_type = TokenType::FUNCTION;};
    FunctionToken(){token_type = TokenType::FUNCTION;}
};

struct ConstantToken : Token{
    Constant c;

    ConstantToken(Constant _c) : c(_c){token_type = TokenType::CONSTANT;}
    ConstantToken(){token_type = TokenType::CONSTANT;}
};

struct FunctionBracketToken : Token{
    FunctionBracketType type;

    FunctionBracketToken(FunctionBracketType _type) : type(_type){token_type = TokenType::FUNCTION_BRACKET;}
    FunctionBracketToken(){token_type = TokenType::FUNCTION_BRACKET;}
};

struct SeparatorToken : Token{
    SeparatorToken(){token_type = TokenType::SEPARATOR;}
};

struct StringToken : Token{
    std::string string;

    StringToken(std::string _string) : string(_string){token_type = TokenType::STRING;}
    StringToken(){token_type = TokenType::STRING;}
};

typedef std::vector<std::unique_ptr<Token> > TokenPtrVec;
typedef std::unique_ptr<Token> TokenPtr;

std::string tokens_to_string(TokenPtrVec& tokens);
std::string debug_tokens_to_string(TokenPtrVec &tokens);

void emplace_token(TokenPtrVec &tokens, size_t token_pos, std::unique_ptr<Token> new_token, std::string &left, std::string &right, size_t &i);

TokenPtrVec tokenize(std::string &expression);