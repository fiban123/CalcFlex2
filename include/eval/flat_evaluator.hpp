#pragma once

#include "tokenizer.hpp"

#include <array>

inline const std::vector<Operator> POW_OPERATOR_VEC = {OPERATOR_POW};

inline const std::vector<std::vector<Operator> > OPERATOR_HIERARCHY = {
    {OPERATOR_MUL, OPERATOR_DIV},
    {OPERATOR_ADD, OPERATOR_SUB}
};

constexpr unsigned POSTFIX_OPERATOR_PRECEDENCE = 0;

size_t find_operator_reverse(TokenPtrVec& tokens, const std::vector<Operator>& hierarchy_level, ssize_t start, ssize_t end);

size_t find_operator(TokenPtrVec& tokens, const std::vector<Operator>& hierarchy_level, size_t start);

void evaluate_operator_at(TokenPtrVec& tokens, size_t i, size_t& d, bool rev);

void evaluate_negation_at(TokenPtrVec& tokens, size_t i, size_t& d);

void evaluate_postfix_operator_at(TokenPtrVec& tokens, size_t& i);

size_t find_negation_reverse(TokenPtrVec& tokens, ssize_t start, ssize_t end);

void evaluate_flat_expression(TokenPtrVec &tokens);