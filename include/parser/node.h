//
// Created by usrccr on 12/10/25.
//

#ifndef LEPAI_PARSER_H
#define LEPAI_PARSER_H
#include <memory>
#include <string>

#include "include/tokenizer/tokenizer.h"

struct Node {
    virtual ~Node() = default;

    virtual std::ostream& print(std::ostream& out) const = 0;

    virtual bool is_operator() const = 0;
};

struct OperatorNode : Node {
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    tok_type type;

    OperatorNode(std::shared_ptr<Node> left = nullptr, tok_type type = {}, std::shared_ptr<Node> right = nullptr);
    ~OperatorNode() override;

    std::ostream& print(std::ostream& out) const override;

    bool is_operator() const override;
};

struct AtomNode : Node {
    std::string atom;

    AtomNode(const std::string& atom);

    std::ostream& print(std::ostream& out) const override;

    bool is_operator() const override;
};

inline std::ostream& operator<<(std::ostream& out, const Node& node) {
    node.print(out);
    return out;
}

#endif //LEPAI_PARSER_H