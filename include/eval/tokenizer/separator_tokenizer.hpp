#pragma once


#include "tokenizer.hpp"

void create_separator_token(TokenPtrVec& tokens, size_t token_pos, std::string& string, size_t string_pos, size_t& i);

void tokenize_separators(TokenPtrVec& tokens);