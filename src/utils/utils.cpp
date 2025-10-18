//
// Created by usrccr on 14/10/25.
//
#include "include/utils/utils.h"

#include <format>
#include <iostream>
#include <regex>
///@file

// Evaluator
Evaluator::Evaluator(const std::unordered_map<std::string, bool>& env_map) : env_map{env_map}, parse_tree{nullptr}{};
Evaluator::Evaluator(std::unordered_map<std::string, bool>&& env_map) : env_map{std::move(env_map)}, parse_tree{nullptr}{};
Evaluator::Evaluator(const Node *parse_tree) : parse_tree{parse_tree}, env_map{{}}{};

bool Evaluator::evaluate(const std::unordered_map<std::string, bool>& env_map) {
    if (this->parse_tree == nullptr)
        throw std::runtime_error("Missing propositional logic statement to evalutate over");

    this->env_map = env_map;
    return evaluate(this->parse_tree);
}


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
        return evaluate(op_node->left.get()) & evaluate(op_node->right.get());
    if (op_node->type == TOK_OR)
        return evaluate(op_node->left.get()) | evaluate(op_node->right.get());
    if (op_node->type == TOK_IMPL)
        return !evaluate(op_node->left.get()) | evaluate(op_node->right.get());
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
    std::cout << root.print();
}

std::tuple<int, int, int> validity_check(const Node& root) {
    std::string linear = root.print();
    linear = std::regex_replace(linear, std::regex(" "), "");
    std::stringstream ss{linear};
    std::string item;

    std::vector<std::string> clauses = {};

    while (std::getline(ss, item, '*')) {
        if (!item.empty())
            clauses.push_back(item);
    }

    bool is_valid = true;
    int valid_clauses = 0, invalid_clauses = 0;

    for (const auto& clause : clauses) {
        std::stringstream css{clause};
        std::unordered_map<std::string, bool> atoms = {};

        while (std::getline(css, item, '+')) {
            if (!item.empty()) {
                atoms[item] = true;
            }
        }

        for (const auto& p : atoms) {
            if (p.first[0] == '~' && !atoms[p.first.substr(1)]) {
                is_valid = false;
                invalid_clauses += 1;
                break;
            }
            if (p.first[0] != '~' && !atoms['~' + p.first]) {
                is_valid = false;
                invalid_clauses += 1;
                break;
            }
        }
    }

    valid_clauses = clauses.size() - invalid_clauses;

    return {is_valid, valid_clauses, invalid_clauses};
}

void print_truth_table(const Node* root, const std::vector<std::string>& templ) {
    Evaluator eval {root};
    for (const auto& atom : templ)
        std::cout << atom << "\t";
    std::cout << "F" << std::endl;
    for (int mask = 0; mask < (1 << templ.size()); mask++) {
        std::unordered_map<std::string, bool> env_map;

        for (int j = templ.size() - 1; j >= 0; j--) {
            if (mask & (1 << j))
                env_map[templ[j]] = true;
            else
                env_map[templ[j]] = false;

            std::cout << env_map[templ[j]] << "\t";
        }

        try{
            std::cout << eval.evaluate(env_map) << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cout << "Missing atom";
            break;
        }
    }
}


