//
// Created by usrccr on 12/10/25.
//
#include "include/parser/node.h"
#include <iostream>
#include <unistd.h>

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
OperatorNode::OperatorNode(std::unique_ptr<Node> left, tok_type type, std::unique_ptr<Node> right) : left {std::move(left)}, right {std::move(right)}, type {type}{
}

OperatorNode::~OperatorNode(){
    // delete left;
    // delete right;
}

std::ostream& OperatorNode::print(std::ostream &out) const {
    if (left.get() == nullptr)
        out << print_enum(type) << " " << *right.get();
    else
        out << *left.get() << " " << print_enum(type) << " " << *right.get();

    return out;
}

bool OperatorNode::is_operator() const {
    return true;
}

//AtomNode
AtomNode::AtomNode(const std::string& atom) : atom {atom}{ // NOLINT(*-pass-by-value)
}

std::ostream& AtomNode::print(std::ostream &out) const{
    out << "Atom(" << atom << ")";
    return out;
}

bool AtomNode::is_operator() const {
    return false;
}








