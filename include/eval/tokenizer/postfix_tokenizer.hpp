#pragma once

#include "tokenizer.hpp"

void create_postfix_operator_token(TokenPtrVec& tokens, size_t token_pos, std::string& string, size_t string_pos, PostfixOperator pop, size_t& i);

size_t find_postfix_operator(std::string& s, PostfixOperator& func_type);

void tokenize_postfix_operator(TokenPtrVec& tokens);
