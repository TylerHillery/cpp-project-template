#pragma once

#include <cstdint>
#include <optional>
#include <string_view>

namespace example {

// Rejects empty input, non-ASCII digits, and values outside uint32_t.
std::optional<std::uint32_t> parse_uint(std::string_view text);

} // namespace example
