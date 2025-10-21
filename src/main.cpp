#include <iostream>
#include <utility>

#include "include/parser/fx_parser.h"
#include "include/parser/node.h"
#include "include/tokenizer/tokenizer.h"
#include "include/utils/converters.h"
#include "include/utils/utils.h"

int main() {
    FxParser p{};

    std::string str = ""; // Provide propositional logic statement here

   auto root = (p.parse_pipeline(str));

    Evaluator evaluator {{{"p", false}, {"q", true}, {"r", true}}}; // Edit truth value of atoms here

    try {
        std::cout << evaluator.evaluate(root.get()) << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;;
    }

    std::cout << compute_height(root.get()) << std::endl;
    //
    auto newr = cnf_pipeline(root);

    validity_check(*newr);

    print_infix(*newr.get());
    std::cout << std::endl;
    print_truth_table(root.get(), {"p", "q", "r"});
}