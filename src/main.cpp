#include "parse_uint.hpp"

#include <iostream>

int main() {
    const auto number = example::parse_uint("123");
    if (!number) {
        std::cerr << "Invalid number\n";
        return 1;
    }
    std::cout << "Parsed: " << *number << '\n';
}
