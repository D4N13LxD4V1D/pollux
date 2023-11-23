#include <MorseCode.hpp>
#include <PolluxCipher.hpp>

#include <iostream>
#include <map>
#include <vector>

auto PolluxCipher::encode(std::string input) -> std::string {
  std::map<char, std::vector<int>> mapping;
  std::cout << "Please choose a mapping for the characters '.', '-', and 'x' "
               "to the numbers 0-9 (eg. .-.-.-.-xx): ";

  for (int i = 0; i < 10; i++) {
    char c;
    std::cin >> c;

    mapping[c].push_back(i);
  }

  std::string morse = MorseCode::encode(input);
  std::string output = "";
  for (char c : morse) {
    std::vector<int> v = mapping[c];
    output += v[rand() % v.size()];
  }

  return output;
}

auto PolluxCipher::decode(std::string input)
    -> std::expected<std::string, std::string> {
  std::map<int, char> mapping;
  std::cout
      << "Please put the known mapping for the characters '.', '-', and 'x' "
         "to the numbers 0-9 (eg. .-.-.-.-xx): ";

  for (int i = 0; i < 10; i++)
    std::cin >> mapping[i];

  std::string morse = "";
  for (char c : input)
    morse += mapping[c - '0'];

  auto output = MorseCode::decode(morse);
  if (!output)
    return std::unexpected(output.error());

  return *output;
}