#pragma once

#include "tokenizer.hpp"

#include <array>
#include <string_view>

void create_operator_token(TokenPtrVec &tokens, size_t token_pos, std::string string, size_t string_pos, Operator op, size_t &i);

size_t find_operator(std::string &s, Operator &op_type);

void tokenize_operators(TokenPtrVec &tokens);