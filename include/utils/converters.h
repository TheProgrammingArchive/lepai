//
// Created by usrccr on 14/10/25.
//

#ifndef LEPAI_CONVERTERS_H
#define LEPAI_CONVERTERS_H
#include "include/parser/node.h"

std::unique_ptr<Node> impl_free(std::unique_ptr<Node> curr);

std::unique_ptr<Node> nnf(std::unique_ptr<Node> curr);

std::unique_ptr<Node> cnf(std::unique_ptr<Node> curr);

std::unique_ptr<Node> distr(std::unique_ptr<Node> n1, std::unique_ptr<Node> n2);

std::unique_ptr<Node> cnf_pipeline(std::unique_ptr<Node> root);

#endif //LEPAI_CONVERTERS_H
