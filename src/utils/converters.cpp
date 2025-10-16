//
// Created by usrccr on 14/10/25.
//
#include "include/utils/converters.h"

#include <ios>

std::unique_ptr<Node> impl_free(std::unique_ptr<Node> curr) {
    if (!curr->is_operator())
        return curr;

    OperatorNode* op_node = dynamic_cast<OperatorNode *>(curr.get());

    if (op_node->type == TOK_IMPL) {
        auto left = std::make_unique<OperatorNode>(std::unique_ptr<Node>(nullptr), TOK_NOT, std::move(op_node->left));
        return std::make_unique<OperatorNode>(std::move(left), TOK_OR, std::move(op_node->right));
    }

    if (op_node->type == TOK_NOT) {
        return std::make_unique<OperatorNode>(nullptr, TOK_NOT, impl_free(std::move(op_node->right)));
    }
    return std::make_unique<OperatorNode>(impl_free(std::move(op_node->left)), op_node->type, impl_free(std::move(op_node->right)));
}

std::unique_ptr<Node> nnf(std::unique_ptr<Node> curr) {
    if (!curr->is_operator())
        return curr;

    OperatorNode* op_node_curr = dynamic_cast<OperatorNode*>(curr.get());

    if (op_node_curr->type != TOK_NOT) {
        auto left = nnf(std::move(op_node_curr->left));
        auto right = nnf(std::move(op_node_curr->right));
        return std::make_unique<OperatorNode>(std::move(left), op_node_curr->type, std::move(right));
    }

    if (op_node_curr->right->is_operator()) {
        OperatorNode* op_right = dynamic_cast<OperatorNode*>(op_node_curr->right.get());

        if (op_right->type == TOK_NOT) {
            auto mv = std::move(op_right->right);
            return nnf(std::move(mv));
        }

        if (op_right->type == TOK_AND) {
            auto new_node = std::make_unique<OperatorNode>(std::make_unique<OperatorNode>(nullptr, TOK_NOT, std::move(op_right->left)), TOK_OR, std::make_unique<OperatorNode>(nullptr, TOK_NOT, std::move(op_right->right)));
            return nnf(std::move(new_node));
        }
        auto new_node = std::make_unique<OperatorNode>(std::make_unique<OperatorNode>(nullptr, TOK_NOT, std::move(op_right->left)), TOK_AND, std::make_unique<OperatorNode>(nullptr, TOK_NOT, std::move(op_right->right)));
        return nnf(std::move(new_node));
    }

    return curr;
}

std::unique_ptr<Node> distr(std::unique_ptr<Node> n1, std::unique_ptr<Node> n2) {
    OperatorNode* n1_op = dynamic_cast<OperatorNode*>(n1.get());
    OperatorNode* n2_op = dynamic_cast<OperatorNode*>(n2.get());

    if (n1_op != nullptr && n1_op->type == TOK_AND)
        return std::make_unique<OperatorNode>(distr(std::move(n1_op->left), std::move(n2)), TOK_AND, distr(std::move(n1_op->right), std::move(n2)));
    if (n2_op != nullptr && n2_op->type == TOK_AND)
        return std::make_unique<OperatorNode>(distr(std::move(n1), std::move(n2_op->left)), TOK_AND, distr(std::move(n1), std::move(n2_op->right)));

    return std::make_unique<OperatorNode>(std::move(n1), TOK_OR, std::move(n2));
}


std::unique_ptr<Node> cnf(std::unique_ptr<Node> curr) {
    if (!curr)
        return curr;

    if (!curr->is_operator() || dynamic_cast<OperatorNode*>(curr.get())->type == TOK_NOT)
        return curr;

    OperatorNode* op_node = dynamic_cast<OperatorNode*>(curr.get());
    if (op_node->type == TOK_AND)
        return std::make_unique<OperatorNode>(cnf(std::move(op_node->left)), TOK_AND, cnf(std::move(op_node->right)));

    return distr(cnf(std::move(op_node->left)), cnf(std::move(op_node->right)));
}

std::unique_ptr<Node> cnf_pipeline(std::unique_ptr<Node> root) {
    auto imp_f = impl_free(std::move(root));
    auto nn_f = nnf(std::move(imp_f));

    auto cnf_final = cnf(std::move(nn_f));

    return cnf_final;
}
