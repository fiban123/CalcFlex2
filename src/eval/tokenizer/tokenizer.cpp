#include "tokenizer.hpp"

#include "bracket_tokenizer.hpp"
#include "number_tokenizer.hpp"
#include "operator_tokenizer.hpp"

#include <vector>
#include <sstream>

std::string tokens_to_string(TokenPtrVec &tokens){
    std::ostringstream out;

    for (size_t i = 0; i < tokens.size(); i++){
        Token *t = tokens[i].get();

        switch (t->token_type){
            case TokenType::NONE:{
                out << "None";
                break;
            }

            case TokenType::NUMBER:{
                NumberToken *np = dynamic_cast<NumberToken *>(t);
                out << np->n->get_str_short(eval_config);
                break;
            }

            case TokenType::BRACKET:{
                BracketToken *bt = dynamic_cast<BracketToken *>(t);
                char bracket_char = bt->type == BRACKET_OPENING ? '(' : ')';
                out << bracket_char;
                break;
            }

            case TokenType::OPERATOR:{
                OperatorToken *ot = dynamic_cast<OperatorToken *>(t);
                std::string operator_string(OPERATORS[static_cast<size_t>(ot->op)]);
                out << operator_string;
                break;
            }

            case TokenType::STRING:{
                StringToken *st = dynamic_cast<StringToken *>(t);
                out << st->string;
                break;
            }
        }
        if (i != tokens.size() - 1){
            out << " ";
        }
    }

    return out.str();
}

std::string debug_tokens_to_string(TokenPtrVec &tokens){
    std::ostringstream out;

    out << "{ ";
    for (size_t i = 0; i < tokens.size(); i++){
        Token *t = tokens[i].get();

        switch (t->token_type){
            case TokenType::NONE:{
                out << "None";
                break;
            }

            case TokenType::NUMBER:{
                NumberToken *np = dynamic_cast<NumberToken *>(t);
                out << np->n->get_str_short(debug_eval_config);
                break;
            }

            case TokenType::BRACKET:{
                BracketToken *bt = dynamic_cast<BracketToken *>(t);
                char bracket_char = bt->type == BRACKET_OPENING ? '(' : ')';
                out << bracket_char;
                break;
            }

            case TokenType::OPERATOR:{
                OperatorToken *ot = dynamic_cast<OperatorToken *>(t);
                std::string operator_string(OPERATORS[static_cast<size_t>(ot->op)]);
                out << operator_string;
                break;
            }

            case TokenType::STRING:{
                StringToken *st = dynamic_cast<StringToken *>(t);
                out << "[str]" << st->string;
                break;
            }
        }
        if (i != tokens.size() - 1){
            out << ", ";
        }
    }
    out << " }";
    out << "\n";

    return out.str();
}

/* emplaces a new token new_token into a string token such that new_token is in
between the left and right strings. decrements i depending on how many new
tokens are inserted */
void emplace_token(TokenPtrVec &tokens, size_t token_pos,
                   std::unique_ptr<Token> new_token, std::string &left,
                   std::string &right, size_t &i) {
  // add left & new token
  if (!left.empty()) {
    tokens[token_pos] = std::make_unique<StringToken>(left);
    tokens.emplace(tokens.begin() + token_pos + 1, std::move(new_token));
    i--;
  } else {
    tokens[token_pos] = std::move(new_token);
  }
  // add right token
  if (!right.empty()) {
    if (!left.empty()) {
      tokens.emplace(tokens.begin() + token_pos + 2, new StringToken(right));
    } else {
      tokens.emplace(tokens.begin() + token_pos + 1, new StringToken(right));
    }
  }
}

TokenPtrVec tokenize(std::string &expression) {
  TokenPtrVec tokens;

  tokenize_brackets(tokens, expression);
  tokenize_operators(tokens);
  tokenize_numbers(tokens);

  return tokens;
}
