#pragma once

#include "tokenizer.hpp"

void create_func_bracket_token(TokenPtrVec& tokens, size_t token_pos, FunctionBracketType type);

void tokenize_func_brackets(TokenPtrVec& tokens);
