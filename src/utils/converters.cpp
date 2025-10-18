//
// Created by usrccr on 14/10/25.
//
#include "include/utils/converters.h"

///@file

std::shared_ptr<Node> impl_free(std::shared_ptr<Node> curr) {
    if (!curr->is_operator())
        return curr;

    OperatorNode* op_node = dynamic_cast<OperatorNode *>(curr.get());

    if (op_node->type == TOK_IMPL) {
        auto left = std::make_shared<OperatorNode>(std::shared_ptr<Node>(nullptr), TOK_NOT, (op_node->left));
        return std::make_shared<OperatorNode>((left), TOK_OR, (op_node->right));
    }

    if (op_node->type == TOK_NOT) {
        return std::make_shared<OperatorNode>(nullptr, TOK_NOT, impl_free((op_node->right)));
    }
    return std::make_shared<OperatorNode>(impl_free((op_node->left)), op_node->type, impl_free((op_node->right)));
}

std::shared_ptr<Node> nnf(std::shared_ptr<Node> curr) {
    if (!curr->is_operator())
        return curr;

    OperatorNode* op_node_curr = dynamic_cast<OperatorNode*>(curr.get());

    if (op_node_curr->type != TOK_NOT) {
        auto left = nnf((op_node_curr->left));
        auto right = nnf((op_node_curr->right));
        return std::make_shared<OperatorNode>((left), op_node_curr->type, (right));
    }

    if (op_node_curr->right->is_operator()) {
        OperatorNode* op_right = dynamic_cast<OperatorNode*>(op_node_curr->right.get());

        if (op_right->type == TOK_NOT) {
            auto mv = (op_right->right);
            return nnf(mv);
        }

        if (op_right->type == TOK_AND) {
            auto new_node = std::make_shared<OperatorNode>(std::make_shared<OperatorNode>(nullptr, TOK_NOT, (op_right->left)), TOK_OR, std::make_shared<OperatorNode>(nullptr, TOK_NOT, (op_right->right)));
            return nnf((new_node));
        }
        auto new_node = std::make_shared<OperatorNode>(std::make_shared<OperatorNode>(nullptr, TOK_NOT, (op_right->left)), TOK_AND, std::make_shared<OperatorNode>(nullptr, TOK_NOT, (op_right->right)));
        return nnf((new_node));
    }

    return curr;
}

std::shared_ptr<Node> distr(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2) {
    auto n1_op = std::dynamic_pointer_cast<OperatorNode>(n1);
    auto n2_op = std::dynamic_pointer_cast<OperatorNode>(n2);

    if (n1_op != nullptr && n1_op->type == TOK_AND)
        return std::make_shared<OperatorNode>(distr((n1_op->left), (n2)), TOK_AND, distr((n1_op->right), (n2)));
    if (n2_op != nullptr && n2_op->type == TOK_AND)
        return std::make_shared<OperatorNode>(distr((n1), (n2_op->left)), TOK_AND, distr((n1), (n2_op->right)));

    return std::make_shared<OperatorNode>((n1), TOK_OR, (n2));
}


std::shared_ptr<Node> cnf(std::shared_ptr<Node> curr) {
    if (!curr)
        return curr;

    if (!curr->is_operator() || std::dynamic_pointer_cast<OperatorNode>(curr)->type == TOK_NOT)
        return curr;

    OperatorNode* op_node = dynamic_cast<OperatorNode*>(curr.get());
    if (op_node->type == TOK_AND)
        return std::make_shared<OperatorNode>(cnf((op_node->left)), TOK_AND, cnf((op_node->right)));

    return distr(cnf((op_node->left)), cnf((op_node->right)));
}

std::shared_ptr<Node> cnf_pipeline(std::shared_ptr<Node> root) {
    auto imp_f = impl_free((root));
    auto nn_f = nnf((imp_f));

    auto cnf_final = cnf((nn_f));

    return cnf_final;
}
