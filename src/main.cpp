#include <iostream>

#include "evaluator.hpp"
#include "gui.hpp"

int main() {
    std::cout << (1u << 6) + 3 << "\n";

    start_gui(evaluate_string);
}
