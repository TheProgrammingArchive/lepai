//
// Created by usrccr on 02/10/25.
//
#include "include/tokenizer/tokenizer.h"
#include <sstream>
#include <iostream>
#include <regex>
///@file

std::vector<token> tokenize(const std::string &logical_expr) {
    std::string l_expr = std::regex_replace(logical_expr, std::regex("\\("), "( ");
    l_expr = std::regex_replace(l_expr, std::regex("\\)"), " )");
    l_expr = std::regex_replace(l_expr, std::regex("\\~"), " ~ ");

    std::stringstream ss{l_expr};
    std::string item;
    std::vector<token> tokens = {};

    while (std::getline(ss, item, ' ')) {
        if (item.empty())
            continue;

        if (item == "+" || item == ">" || item == "~" || item == "*") {
            if (item == "+")
                tokens.push_back({TOK_OR, ""});
            else if (item == "*")
                tokens.push_back({TOK_AND, ""});
            else if (item == ">")
                tokens.push_back({TOK_IMPL, ""});
            else
                tokens.push_back({TOK_NOT, ""});
        }

        else if (item == "(")
            tokens.push_back({TOK_LPAREN, ""});
        else if (item == ")")
            tokens.push_back({TOK_RPAREN, ""});
        else
            tokens.push_back({ATOM, item});
    }

    return tokens;
}