#include "parse_uint.hpp"

#include <limits>

namespace example {

std::optional<std::uint32_t> parse_uint(std::string_view text) {
    if (text.empty()) {
        return std::nullopt;
    }

    std::uint32_t value = 0;
    for (char character : text) {
        if (character < '0' || character > '9') {
            return std::nullopt;
        }
        const auto digit = static_cast<std::uint32_t>(character - '0');
        if (value > (std::numeric_limits<std::uint32_t>::max() - digit) / 10) {
            return std::nullopt;
        }
        value = value * 10 + digit;
    }
    return value;
}

} // namespace example
