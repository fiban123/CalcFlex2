#pragma once

#include "dynamic_vec.hpp"
#include "functions.hpp"

#define OPERATORS_MACRO \
    X(OPERATOR_NONE, "") \
    X(OPERATOR_ADD, "+") \
    X(OPERATOR_SUB, "-") \
    X(OPERATOR_MUL, "*") \
    X(OPERATOR_DIV, "/") \
    X(OPERATOR_POW, "^")

#define POSTFIX_OPERATORS_MACRO \
    X(POSTFIX_FACTORIAL, "!") \
    X(POSTFIX_PRIMORIAL, "#") 


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
    #define X(a, b) a,
    OPERATORS_MACRO
    #undef X
    OPERATOR_COUNT
};

enum PostfixOperator{
    #define X(a, b) a,
    POSTFIX_OPERATORS_MACRO
    #undef X
    POSTFIX_OPERATOR_COUNT
};


inline constexpr std::array<std::string_view, OPERATOR_COUNT> OPERATORS = {
    #define X(a, b) b,
    OPERATORS_MACRO
    #undef x
};

inline constexpr std::array<std::string_view, POSTFIX_OPERATOR_COUNT> POSTFIX_OPERATORS = {
    #define X(a, b) b,
    POSTFIX_OPERATORS_MACRO
    #undef x
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

struct NegationToken : Token{
    NegationToken(){token_type = TokenType::NEGATION;}
};

struct FunctionToken : Token{
    MathPrimitive func;

    FunctionToken(MathPrimitive _func) : func(_func){token_type = TokenType::FUNCTION;};
    FunctionToken(){token_type = TokenType::FUNCTION;}
};

struct ConstantToken : Token{
    MathPrimitive c;

    ConstantToken(MathPrimitive _c) : c(_c){token_type = TokenType::CONSTANT;}
    ConstantToken(){token_type = TokenType::CONSTANT;}
};

struct PostfixOperatorToken : Token{
    PostfixOperator pop;

    PostfixOperatorToken(PostfixOperator _pop) : pop(_pop){token_type = TokenType::POSTFIX_OPERATOR;}
    PostfixOperatorToken(){token_type = TokenType::POSTFIX_OPERATOR;}
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
typedef std::vector<TokenPtrVec> Args;

std::string tokens_to_string(TokenPtrVec& tokens);
std::string debug_tokens_to_string(TokenPtrVec &tokens);

void emplace_token(TokenPtrVec &tokens, size_t token_pos, std::unique_ptr<Token> new_token, std::string &left, std::string &right, size_t &i);

TokenPtrVec tokenize(std::string &expression);