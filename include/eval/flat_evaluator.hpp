#pragma once

#include "tokenizer.hpp"

#include <array>

inline const std::vector<std::vector<Operator> > OPERATOR_HIERARCHY = {
    {OPERATOR_POW},
    {OPERATOR_MUL, OPERATOR_DIV},
    {OPERATOR_ADD, OPERATOR_SUB}
};

size_t find_operator(TokenPtrVec &tokens, const std::vector<Operator> &hierarchy_level, size_t start);

void evaluate_operator_at(TokenPtrVec &tokens, size_t i, size_t &d);

void evaluate_flat_expression(TokenPtrVec &tokens);