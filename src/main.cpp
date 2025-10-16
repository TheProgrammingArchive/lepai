#include <iostream>
#include <utility>

#include "include/parser/fx_parser.h"
#include "include/parser/node.h"
#include "include/tokenizer/tokenizer.h"
#include "include/utils/converters.h"
#include "include/utils/utils.h"

class Test {
public:
    int x;

    Test(Test&& mv_test)  noexcept : x {mv_test.x} {
        std::cout << "moving";
    };
    Test(const Test& t) : x {t.x} {
        std::cout << "copy constructor";
    }
    Test(int x) : x {x} {
        std::cout << "Regular";
    }
};

class Handler {
private:
    Test t;

public:
    Handler(Test&& t) : t {(t)} {

    }

    void doSomething() {
        this->t.x += 3;
    }
};

// std::string print_enum(int t) {
//     switch (t) {
//         case 0:
//             return "TOK_AND";
//         case 1:
//             return "TOK_OR";
//         case 2:
//             return "TOK_IMPL";
//         case 3:
//             return "TOK_NOT";
//         case 4:
//             return "";
//         case 5:
//             return "TOK_LPAREN";
//         case 6:
//             return "TOK_RPAREN";
//         default:
//             return "";
//     }
// }

int main() {
    FxParser p{};

    auto root = (p.parse_pipeline("p > ~(r * (p + ~q + ~(z > e))"));

    Evaluator evaluator {{{"p", false}, {"q", true}, {"r", true}}};

    try {
        std::cout << evaluator.evaluate(root.get()) << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;;
    }

    std::cout << compute_height(root.get());

    auto newr = cnf_pipeline((root));

    print_infix(*newr.get());
}