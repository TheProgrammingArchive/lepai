//
// Created by usrccr on 14/10/25.
//

#ifndef LEPAI_UTILS_H
#define LEPAI_UTILS_H
#include <map>
#include <unordered_map>

#include "include/parser/node.h"

///@file

/**
 * @brief struct representing Evaluator
 * Used to evaluate a propositional logic statement or fixed set of truth values or evaluate a fixed propositional logic statement over a set of truth values
 */
struct Evaluator {
    std::unordered_map<std::string, bool> env_map;
    const Node* parse_tree;

    /**
     * @brief Constructor for evaluator with fixed truth value set
     * @param env_map set of truth values of all atoms, copies if an lvalue is passed and moves if an rvalue is passed
     */
    Evaluator(const std::unordered_map<std::string, bool>& env_map);
    Evaluator(std::unordered_map<std::string, bool>&& env_map);

    /**
     *
     * @brief Constructor for evaluator with fixed parse tree
     * @param parse_tree pointer to root of parse tree
     */
    Evaluator(const Node* parse_tree);

    bool evaluate(const Node* node) const;
    bool evaluate(const std::unordered_map<std::string, bool>& env_map);
};

int compute_height(Node* root);

void print_infix(const Node& root);

std::tuple<int, int, int> validity_check(const Node& root);

void print_truth_table(const Node* root, const std::vector<std::string>& templ);

#endif //LEPAI_UTILS_H