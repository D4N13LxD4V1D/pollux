#ifndef MORSE_CODE
#define MORSE_CODE

#include <expected>
#include <string>

namespace MorseCode {
auto encode(std::string input) -> std::string;
auto decode(std::string input) -> std::expected<std::string, std::string>;
}; // namespace MorseCode

#endif // MORSE_CODE