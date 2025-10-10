#pragma once

#include "tokenizer.hpp"

void create_number_token(TokenPtrVec &tokens, StringToken *str_token, size_t string_i, size_t &token_i);

void tokenize_numbers(TokenPtrVec &tokens);

inline bool is_number(char c){ return (c >= '0' && c <= '9') || c == '.'; }