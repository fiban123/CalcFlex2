#pragma once

#include "tokenizer.hpp"

void create_primitive_token(TokenPtrVec& tokens, size_t token_pos, std::string& string, size_t string_pos, MathPrimitive p, size_t& i);

size_t find_primitive(std::string& s, MathPrimitive& func_type);

void tokenize_primitive(TokenPtrVec& tokens);
