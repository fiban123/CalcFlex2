#include "flat_evaluator.hpp"

#include "dynamic_vec_math.hpp"
#include "pow.hpp"
#include "negate.hpp"
#include "factorial.hpp"

size_t find_operator_reverse(TokenPtrVec& tokens, const std::vector<Operator>& hierarchy_level, ssize_t start, ssize_t end) {
    for (ssize_t i = start; i >= end; i--) {
        if (tokens[i]->token_type == TokenType::OPERATOR) {
            // found operator token
            OperatorToken* ot = dynamic_cast<OperatorToken*>(tokens[i].get());

            for (unsigned j = 0; j < hierarchy_level.size(); j++) {
                if (hierarchy_level[j] == ot->op) {
                    // found operator
                    return i;
                }
            }
        }
    }
    return std::string::npos;
}

size_t find_operator(TokenPtrVec& tokens, const std::vector<Operator>& hierarchy_level, size_t start) {
    for (ssize_t i = start; i < tokens.size(); i++) {
        if (tokens[i]->token_type == TokenType::OPERATOR) {
            // found operator token
            OperatorToken* ot = dynamic_cast<OperatorToken*>(tokens[i].get());

            for (unsigned j = 0; j < hierarchy_level.size(); j++) {
                if (hierarchy_level[j] == ot->op) {
                    // found operator
                    return i;
                }
            }
        }
    }
    return std::string::npos;
}

/* try evaluating an operator at a given index i. decrements d depending on how
 * many elements are erased*/
void evaluate_operator_at(TokenPtrVec& tokens, size_t i, size_t& d, bool rev = false) {
    std::cout << "eval operator" << i << std::endl;
    //1+1
    //2
    if (!rev){d += 2;} else {d-=2;}
    OperatorToken* ot = dynamic_cast<OperatorToken*>(tokens[i].get());

    if (i == 0 || i == tokens.size() - 1) {
        // left and right numbers dont exist
        return;
    }

    Token* left_tok = tokens[i - 1].get();
    Token* right_tok = tokens[i + 1].get();

    if (left_tok->token_type != TokenType::NUMBER || right_tok->token_type != TokenType::NUMBER) {
        // left and right are not numbers
        return;
    }


    NumberToken* left_num_tok = dynamic_cast<NumberToken*>(left_tok);
    NumberToken* right_num_tok = dynamic_cast<NumberToken*>(right_tok);

    DynamicVec* left_num = left_num_tok->n.get();
    DynamicVec* right_num = right_num_tok->n.get();

    std::unique_ptr<DynamicVec> result_num;

    switch (ot->op) {
    case OPERATOR_ADD: {
        result_num = *left_num + *right_num;
        break;
    }
    case OPERATOR_SUB: {
        result_num = *left_num - *right_num;
        break;
    }
    case OPERATOR_MUL: {
        result_num = *left_num * *right_num;
        break;
    }
    case OPERATOR_DIV: {
        result_num = *left_num / *right_num;
        break;
    }
    case OPERATOR_POW: {
        result_num = vec_pow(*left_num, *right_num);
        break;
    }
    }

    std::unique_ptr<NumberToken> result_tok = std::make_unique<NumberToken>(std::move(result_num));

    // delete old numbers & operators
    tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);

    if (!rev){d -= 2;}
    tokens[i - 1] = std::move(result_tok);
}

void evaluate_negation_at(TokenPtrVec& tokens, size_t i, size_t& d){
    std::cout << "eval negation" << i << std::endl;

    d--;

    // make sure next token is a number
    if (tokens[i + 1]->token_type != TokenType::NUMBER){
        return;
    }

    NumberToken* num = dynamic_cast<NumberToken*>(tokens[i + 1].get());

    vec_negate(*(num->n));

    //num->n = std::make_unique<DynamicVec>("78", 0);

    tokens.erase(tokens.begin() + i);
}

void evaluate_postfix_operator_at(TokenPtrVec& tokens, size_t& i){
    // check if previous token is a number
    if (tokens[i - 1]->token_type == TokenType::NUMBER){
        NumberToken* num = dynamic_cast<NumberToken*>(tokens[i - 1].get());

        std::cout << "aaaa" << num->n->get_str_short(eval_config) << std::endl;

        vec_factorial(*(num->n));

        // remove factorial
        tokens.erase(tokens.begin() + i);
    }
}

size_t find_negation_reverse(TokenPtrVec& tokens, ssize_t start, ssize_t end){
    for (ssize_t i = start; i >= end; i--){
        if (tokens[i]->token_type == TokenType::NEGATION){
            return i;
        }
    }
    return std::string::npos;
}


void evaluate_postfix_operators(TokenPtrVec& tokens){
    for (size_t i = 1; i < tokens.size(); i++){
        if (tokens[i]->token_type == TokenType::POSTFIX_OPERATOR){
            evaluate_postfix_operator_at(tokens, i);
        }
    }
}

/*evaluates a flat expression as far as possible. a flat expression is
just an expression that does not contain brackets or functions*/
void evaluate_flat_expression(TokenPtrVec& tokens) {
    // evaluate negation and exponentiation first.

    size_t start = tokens.size() - 1;
    size_t end = 0;

    size_t next_pow_op = find_operator_reverse(tokens, POW_OPERATOR_VEC, start, end);
    size_t next_neg_op = find_negation_reverse(tokens, start, end);

    while (next_pow_op != std::string::npos || next_neg_op != std::string::npos){

        std::cout << debug_tokens_to_string(tokens);

        std::cout << "neg" << next_neg_op << "pow" << next_pow_op << "start" << end << std::endl;
        if (next_pow_op == std::string::npos){
            start = next_neg_op;
            evaluate_negation_at(tokens, next_neg_op, start);
        }
        else if (next_neg_op == std::string::npos){
            start = next_pow_op;
            evaluate_operator_at(tokens, next_pow_op, start, true);
        }
        else if (next_neg_op < next_pow_op){
            // pow operator is last
            start = next_pow_op;
            evaluate_operator_at(tokens, next_pow_op, start, true);
        }
        else{
            // neg is last
            start = next_neg_op;
            evaluate_negation_at(tokens, next_neg_op, start);
        }
        //start = std::min(start, tokens.size() - 1);
        
        std::cout << "start=" << start << std::endl;

        next_pow_op = find_operator_reverse(tokens, POW_OPERATOR_VEC, start, end);
        next_neg_op = find_negation_reverse(tokens, start, end);
    }


    // evaluate the rest
    for (size_t l = 0; l < OPERATOR_HIERARCHY.size(); l++){
        const std::vector<Operator>& hierarchy_level = OPERATOR_HIERARCHY[l];

        if (l == POSTFIX_OPERATOR_PRECEDENCE){
            evaluate_postfix_operators(tokens);
        }

        size_t start = 0;
        size_t i = find_operator(tokens, hierarchy_level, start);

        while (i != SIZE_MAX) {
            start = i;

            evaluate_operator_at(tokens, i, start);

            i = find_operator(tokens, hierarchy_level, start);
        }
    }
}
