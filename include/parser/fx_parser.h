//
// Created by usrccr on 13/10/25.
//

#ifndef LEPAI_FX_PARSER_H
#define LEPAI_FX_PARSER_H
#include <vector>

#include "node.h"
#include "include/tokenizer/tokenizer.h"
///@file

/**
 * @brief struct representing the parser, converts the propositional logic statement from infix to prefix and then generates a parse tree
 */
class FxParser {
private:
    int position;
    std::vector<token> prefix;

    /**
     * Converts an infix token set to prefix token set
     * @param tokens vector of tokens in infix form
     * @return vector of tokens in prefix form
     */
    std::vector<token> convert_to_prefix(const std::vector<token>& tokens);

    /**
     * Converts a prefix token set to parse tree
     * @param tok vector of tokens in prefix form
     * @return pointer to root of parse tree
     */
    std::shared_ptr<Node> generate_parse_tree(const token& tok);

    token& next();

public:
    /**
     * parameterless constructor for FxParser
     */
    FxParser();
    /**
     * Takes in a propositional logic statement as a string and returns a pointer to the root of its parse tree
     * @param str propositional logic statement as a string
     * @return pointer to root of parse tree
     */
    std::shared_ptr<Node> parse_pipeline(const std::string& str);
};

#endif //LEPAI_FX_PARSER_H
