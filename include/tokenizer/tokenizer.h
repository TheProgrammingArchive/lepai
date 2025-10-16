//
// Created by usrccr on 02/10/25.
//

#ifndef LEPAI_TOKENIZER_H
#define LEPAI_TOKENIZER_H
#include <string>
#include <vector>

enum tok_type {
    TOK_AND,
    TOK_OR,
    TOK_IMPL,
    TOK_NOT,
    ATOM,

    TOK_LPAREN,
    TOK_RPAREN
};

struct token {
    tok_type type;
    std::string atom;
};

std::vector<token> tokenize(const std::string& logical_expr);

#endif //LEPAI_TOKENIZER_H