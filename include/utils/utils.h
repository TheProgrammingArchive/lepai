//
// Created by usrccr on 14/10/25.
//

#ifndef LEPAI_UTILS_H
#define LEPAI_UTILS_H
#include <map>
#include <unordered_map>

#include "include/parser/node.h"

struct Evaluator {
    std::unordered_map<std::string, bool> env_map;

    Evaluator(const std::unordered_map<std::string, bool>& env_map);
    Evaluator(std::unordered_map<std::string, bool>&& env_map);

    bool evaluate(const Node* node) const;
};

int compute_height(Node* root);

void print_infix(const Node& root);

bool validity_check(Node* root);

#endif //LEPAI_UTILS_H