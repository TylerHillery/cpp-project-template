#include "parse_uint.hpp"

#include <cstdint>
#include <iostream>
#include <optional>
#include <string_view>

namespace {

int failures = 0;

void check(std::string_view input, std::optional<std::uint32_t> expected) {
    const auto actual = example::parse_uint(input);
    if (actual != expected) {
        std::cerr << "parse_uint failed for input '" << input << "'\n";
        ++failures;
    }
}

} // namespace

int main() {
    check("0", 0);
    check("123", 123);
    check("0007", 7);
    check("4294967295", UINT32_MAX);
    check("", std::nullopt);
    check("-1", std::nullopt);
    check("12x", std::nullopt);
    check(" 3", std::nullopt);
    check("4294967296", std::nullopt);

    if (failures != 0) {
        std::cerr << failures << " test(s) failed\n";
        return 1;
    }
    std::cout << "All tests passed\n";
}
