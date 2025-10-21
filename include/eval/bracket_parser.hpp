#pragma once

#include "tokenizer.hpp"

size_t arb_find_closing_bracket(TokenPtrVec& tokens, size_t i);

size_t find_closing_bracket(TokenPtrVec& tokens, size_t i);

size_t find_closing_function_bracket(TokenPtrVec& tokens, size_t i);
