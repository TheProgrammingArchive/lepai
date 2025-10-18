//
// Created by usrccr on 02/10/25.
//

#ifndef LEPAI_TOKENIZER_H
#define LEPAI_TOKENIZER_H
#include <string>
#include <vector>

///@file

/**
 * @brief enum representing different tokens that a propositional logic statement is broken down into
 */
enum tok_type {
    TOK_AND,
    TOK_OR,
    TOK_IMPL,
    TOK_NOT,
    ATOM,

    TOK_LPAREN,
    TOK_RPAREN
};

/**
 * @brief struct representing a singular token
 * @note atom is an empty string for operator tokens
 */
struct token {
    tok_type type;
    std::string atom;
};

/**
 * Tokenizes a propositional logic statement
 * @param logical_expr propositional logic statement as a string
 * @return vector of tokens
 */
std::vector<token> tokenize(const std::string& logical_expr);

#endif //LEPAI_TOKENIZER_H