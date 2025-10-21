#pragma once

#include "tokenizer.hpp"

constexpr Operator NEGATION_OPERATOR = OPERATOR_SUB;

void create_negation_token(TokenPtrVec& tokens, size_t token_pos);

void tokenize_negation(TokenPtrVec& tokens);
