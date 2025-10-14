#include "flat_evaluator.hpp"

#include "dynamic_vec_math.hpp"
#include "pow.hpp"

size_t find_operator(TokenPtrVec& tokens, const std::vector<Operator>& hierarchy_level, size_t start) {
    for (size_t i = start; i < tokens.size(); i++) {
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
    return SIZE_MAX;
}

/* try evaluating an operator at a given index i. decrements d depending on how
 * many elements are erased*/
void evaluate_operator_at(TokenPtrVec& tokens, size_t i, size_t& d) {
    d++;
    OperatorToken* ot = dynamic_cast<OperatorToken*>(tokens[i].get());

    if (i == 0 || i == tokens.size() - 1) {
        // left and right numbers dont exist
        return;
    }

    std::cout << "1\n";

    Token* left_tok = tokens[i - 1].get();
    Token* right_tok = tokens[i + 1].get();

    if (left_tok->token_type != TokenType::NUMBER || right_tok->token_type != TokenType::NUMBER) {
        // left and right are not numbers
        return;
    }

    std::cout << "2\n";

    NumberToken* left_num_tok = dynamic_cast<NumberToken*>(left_tok);
    NumberToken* right_num_tok = dynamic_cast<NumberToken*>(right_tok);

    DynamicVec* left_num = left_num_tok->n.get();
    DynamicVec* right_num = right_num_tok->n.get();
    std::cout << "3\n";

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
    std::cout << "5\n";

    d--;
    tokens[i - 1] = std::move(result_tok);
}

/*evaluates a flat expression as far as possible. a flat expression is
just an expression that contains only numbers and operators*/
void evaluate_flat_expression(TokenPtrVec& tokens) {
    for (const std::vector<Operator>& hierarchy_level : OPERATOR_HIERARCHY) {
        size_t start = 0;
        size_t i = find_operator(tokens, hierarchy_level, start);

        while (i != SIZE_MAX) {
            evaluate_operator_at(tokens, i, start);

            i = find_operator(tokens, hierarchy_level, start);
        }
    }
}
