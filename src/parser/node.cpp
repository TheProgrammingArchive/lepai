//
// Created by usrccr on 12/10/25.
//
#include "include/parser/node.h"
#include <iostream>
#include <unistd.h>

///@file

std::string print_enum(int t) {
    switch (t) {
        case 0:
            return "*";
        case 1:
            return "+";
        case 2:
            return ">";
        case 3:
            return "~";
        case 4:
            return "";
        case 5:
            return "(";
        case 6:
            return ")";
        default:
            return "";
    }
}

// OperatorNode
OperatorNode::OperatorNode(std::shared_ptr<Node> left, tok_type type, std::shared_ptr<Node> right) : left {std::move(left)}, right {std::move(right)}, type {type}{
}

std::string OperatorNode::print() const {
    if (left.get() == nullptr)
        return  print_enum(type) + " " + right.get()->print();

    return left.get()->print() + " " + print_enum(type) + " " + right.get()->print();

}

bool OperatorNode::is_operator() const {
    return true;
}

//AtomNode
AtomNode::AtomNode(const std::string& atom) : atom {atom}{ // NOLINT(*-pass-by-value)
}

std::string AtomNode::print() const {
    return atom;
}


bool AtomNode::is_operator() const {
    return false;
}








