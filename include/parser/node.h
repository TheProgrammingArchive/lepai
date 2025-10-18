//
// Created by usrccr on 12/10/25.
//

#ifndef LEPAI_PARSER_H
#define LEPAI_PARSER_H
#include <memory>
#include <string>

#include "include/tokenizer/tokenizer.h"

///@file

/**
 * Internal representation of Node in memory, contains purely virtual methods that are overriden by specific node types
 */
struct Node {
    virtual ~Node() = default;

    /** Recursively print parse tree */
    virtual std::string print() const = 0;

    /** Returns whether the node object is an operator or an atom */
    virtual bool is_operator() const = 0;
};

/**
 * struct representing OperatorNode, holds strong references to both its left and right nodes
 */
struct OperatorNode : Node {
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    tok_type type;

    /**
     * @brief Constructor for OperatorNode
     * @param left pointer to root of left subtree
     * @param type (AND/OR/IMPLIES/NOT)
     * @param right pointer to root of right subtree
     */
    OperatorNode(std::shared_ptr<Node> left = nullptr, tok_type type = {}, std::shared_ptr<Node> right = nullptr);

    std::string print() const override;

    bool is_operator() const override;
};

/**
 * struct representing AtomNode, holds the atom string
 */
struct AtomNode : Node {
    std::string atom;

    /**
     * @brief Constructor for AtomNode
     * @param atom atom string
     */
    AtomNode(const std::string& atom);

    std::string print() const override;

    bool is_operator() const override;
};

#endif //LEPAI_PARSER_H