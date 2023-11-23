#ifndef POLLUX_CIPHER
#define POLLUX_CIPHER

#include <expected>
#include <string>

namespace PolluxCipher {
auto encode(std::string input) -> std::string;
auto decode(std::string input) -> std::expected<std::string, std::string>;
}; // namespace PolluxCipher

#endif // POLLUX_CIPHER