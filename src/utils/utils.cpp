//
// Created by usrccr on 14/10/25.
//
#include "include/utils/utils.h"

#include <format>
#include <iostream>

// Evaluator
Evaluator::Evaluator(const std::unordered_map<std::string, bool>& env_map) : env_map{env_map}{};
Evaluator::Evaluator(std::unordered_map<std::string, bool> &&env_map) : env_map{std::move(env_map)}{};


bool Evaluator::evaluate(const Node *node) const {
    if (!node->is_operator()) {
        try {
            bool atom = this->env_map.at(dynamic_cast<const AtomNode*>(node)->atom);
            return atom;
        }
        catch (const std::out_of_range& e) {
            throw std::runtime_error(std::format("Unknown atom: {}", dynamic_cast<const AtomNode*>(node)->atom));
        }
    }

    const OperatorNode *op_node = dynamic_cast<const OperatorNode *>(node);
    if (op_node->type == TOK_AND)
        return evaluate(op_node->left.get()) && evaluate(op_node->right.get());
    if (op_node->type == TOK_OR)
        return evaluate(op_node->left.get()) || evaluate(op_node->right.get());
    if (op_node->type == TOK_IMPL)
        return !evaluate(op_node->left.get()) || evaluate(op_node->right.get());
    return !evaluate(op_node->right.get());
}


int compute_height(Node* root) {
    if (!root)
        return 0;

    if (!root->is_operator())
        return 1;

    return std::max(compute_height(dynamic_cast<OperatorNode*>(root)->left.get()), compute_height(dynamic_cast<OperatorNode*>(root)->right.get())) + 1;
}

void print_infix(const Node& root) {
    std::cout << root;
}
