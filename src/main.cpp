#include <iostream>
#include <utility>

#include "include/parser/fx_parser.h"
#include "include/parser/node.h"
#include "include/tokenizer/tokenizer.h"
#include "include/utils/converters.h"
#include "include/utils/utils.h"

int main() {
    FxParser p{};

    auto root = (p.parse_pipeline("(1 + ~1) * (2 + 3) * (~3 + ~4)"));

    Evaluator evaluator {{{"p", false}, {"q", true}, {"r", true}}};
    //
    try {
        std::cout << evaluator.evaluate(root.get()) << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;;
    }
    //
    std::cout << compute_height(root.get()) << std::endl;
    //
    auto newr = cnf_pipeline(root);

    // std::cout << "KJASDF" << std::get<1>(validity_check(*newr)) << std::endl;

    print_infix(*newr.get());
    print_truth_table(root.get(), {"p", "q", "r"});
}