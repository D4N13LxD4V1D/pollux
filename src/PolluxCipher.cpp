#include <MorseCode.hpp>
#include <PolluxCipher.hpp>

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <map>
#include <vector>

auto PolluxCipher::encode(std::string input)
    -> std::expected<std::string, std::string> {
  std::map<char, std::vector<int>> mapping;
  std::cout << "Please choose a mapping for the characters '.', '-', and 'x' "
               "to the numbers 0-9 (eg. .-.-.-.-xx): ";

  std::string line;
  std::getline(std::cin, line);

  if (line.size() != 10)
    return std::unexpected("Invalid mapping! Please try again.");

  for (int i = 0; i < 10; i++)
    mapping[line[i]].push_back(i);

  std::srand(std::time(nullptr));

  std::string morse = MorseCode::encode(input);
  std::string output = "";
  for (char c : morse) {
    std::vector<int> v = mapping[c];
    output += std::to_string(v[std::rand() % v.size()]);
  }

  return output;
}

auto PolluxCipher::decode(std::string input)
    -> std::expected<std::string, std::string> {
  std::map<int, char> mapping;
  std::cout
      << "Please put the known mapping for the characters '.', '-', and 'x' "
         "to the numbers 0-9 (eg. .-.-.-.-xx): ";

  std::string line;
  std::getline(std::cin, line);

  if (line.size() != 10)
    return std::unexpected("Invalid mapping! Please try again.");

  for (int i = 0; i < 10; i++)
    mapping[i] = line[i];

  std::string morse = "";
  for (char c : input)
    morse += mapping[c - '0'];

  auto output = MorseCode::decode(morse);
  if (!output)
    return std::unexpected(output.error());

  return *output;
}