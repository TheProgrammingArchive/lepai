//
// Created by usrccr on 14/10/25.
//

#ifndef LEPAI_CONVERTERS_H
#define LEPAI_CONVERTERS_H
#include "include/parser/node.h"

std::shared_ptr<Node> impl_free(std::shared_ptr<Node> curr);

std::shared_ptr<Node> nnf(std::shared_ptr<Node> curr);

std::shared_ptr<Node> cnf(std::shared_ptr<Node> curr);

std::shared_ptr<Node> distr(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2);

std::shared_ptr<Node> cnf_pipeline(std::shared_ptr<Node> root);

#endif //LEPAI_CONVERTERS_H
