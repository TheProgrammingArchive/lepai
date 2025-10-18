//
// Created by usrccr on 13/10/25.
//

#include "include/parser/fx_parser.h"
#include <algorithm>
#include <ranges>

///@file

int get_precedence(tok_type ty) {
    if (ty == TOK_NOT)
        return 4;
    if (ty == TOK_AND)
        return 3;
    if (ty == TOK_OR)
        return 2;
    if (ty == TOK_IMPL)
        return 1;
    return 0;
}

FxParser::FxParser() : position{0}{};


std::vector<token> FxParser::convert_to_prefix(const std::vector<token> &tokens) {
    std::vector<token> stack = {};
    std::vector<token> prefix = {};

    std::vector<token> tk = tokens;
    std::reverse(tk.begin(), tk.end());
    for (const token& tok : tk) {
        if (tok.type == TOK_RPAREN)
            stack.push_back(tok);

        else if (tok.type == TOK_LPAREN) {
            while (!stack.empty() && stack.back().type != TOK_RPAREN) {
                token elem = stack.back();
                stack.pop_back();
                prefix.push_back(elem);
            }
            if (!stack.empty())
                stack.pop_back();
        }

        else if (tok.type == TOK_AND || tok.type == TOK_OR || tok.type == TOK_IMPL || tok.type == TOK_NOT) {
            while (!stack.empty() && stack.back().type != TOK_RPAREN && get_precedence(stack.back().type) > get_precedence(tok.type)) {
                token elem = stack.back();
                stack.pop_back();
                prefix.push_back(elem);
            }
            stack.push_back(tok);
        }

        else
            prefix.push_back(tok);
    }

    while (!stack.empty()) {
        token elem = stack.back();
        stack.pop_back();
        prefix.push_back(elem);
    }

    std::reverse(prefix.begin(), prefix.end());
    this->prefix = prefix;
    return prefix;
}

token& FxParser::next() {
    return prefix[++this->position];
}


std::shared_ptr<Node> FxParser::generate_parse_tree(const token& tok) {
    if (!tok.atom.empty()) {
        return std::make_shared<AtomNode>(tok.atom);
    }

    if (tok.type == TOK_NOT) {
        auto right = generate_parse_tree(next());
        return std::make_shared<OperatorNode>(std::shared_ptr<Node>(nullptr), tok.type, std::move(right));
    }

    auto left = generate_parse_tree(next());
    auto right = generate_parse_tree(next());

    return std::make_shared<OperatorNode>(std::move(left), tok.type, std::move(right));
}

std::shared_ptr<Node> FxParser::parse_pipeline(const std::string &str) {
    std::vector<token> tokens = tokenize(str);
    convert_to_prefix(tokens);

    return generate_parse_tree(this->prefix[0]);
}
