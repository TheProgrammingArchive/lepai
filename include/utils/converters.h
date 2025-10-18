//
// Created by usrccr on 14/10/25.
//

#ifndef LEPAI_CONVERTERS_H
#define LEPAI_CONVERTERS_H
#include "include/parser/node.h"
///@file


/**
 * Converts a standard parse tree to an implication free form parse tree
 * @param curr pointer to root of parse tree
 * @return root of parse tree of the equivalent statement that is implication free
 */
std::shared_ptr<Node> impl_free(std::shared_ptr<Node> curr);

/**
 * Converts an implication free form parse tree to a negation normal form
 * @param curr pointer to root of parse tree that is in impl free form
 * @return root of parse tree of the equivalent statement that is in NNF
 */
std::shared_ptr<Node> nnf(std::shared_ptr<Node> curr);

/**
 * Converts an NNF parse tree to its final CNF form
 * @param curr pointer to root of parse tree that is in NNF
 * @return root of parse tree of the equivalent statement that is in CNF
 */
std::shared_ptr<Node> cnf(std::shared_ptr<Node> curr);

/**
 * Distribute OR over AND
 * @param n1 pointer to root of left subtree of the logical OR operator node
 * @param n2 pointer to root of right subtree of the logical OR operator node
 * @return pointer to root of subtree that has been distributed
 */
std::shared_ptr<Node> distr(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2);

/**
 * Converts a propositional logic statement to its CNF form
 * @param root pointer to root of normal parse tree
 * @return pointer to root of parse tree of CNF form
 */
std::shared_ptr<Node> cnf_pipeline(std::shared_ptr<Node> root);

#endif //LEPAI_CONVERTERS_H
