//
// Created by usrccr on 13/10/25.
//

#ifndef LEPAI_FX_PARSER_H
#define LEPAI_FX_PARSER_H
#include <vector>

#include "node.h"
#include "include/tokenizer/tokenizer.h"

class FxParser {
private:
    int position;
    std::vector<token> prefix;

public:
    FxParser() : position{0}{};

    std::vector<token> convert_to_prefix(const std::vector<token>& tokens);

    std::shared_ptr<Node> generate_parse_tree(const token& tok);

    std::shared_ptr<Node> parse_pipeline(const std::string& str);

    token& next();
};

#endif //LEPAI_FX_PARSER_H
