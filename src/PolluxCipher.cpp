#include <English.hpp>
#include <MorseCode.hpp>
#include <PolluxCipher.hpp>

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <map>
#include <vector>

auto PolluxCipher::encode(std::string input)
    -> std::expected<std::string, std::string> {
  std::cout << "Please choose a mapping for the characters '.', '-', and 'x' "
               "to the numbers 0-9 (eg. .-.-.-.-xx): ";

  std::string line;
  std::getline(std::cin, line);

  if (line.size() != 10)
    return std::unexpected("Invalid mapping! Please try again.");

  std::map<char, std::vector<int>> mapping;
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
  std::cout
      << "Please put the known mapping for the characters '.', '-', and 'x' "
         "to the numbers 0-9 and put '?' for the unknowns (eg. .-??.-.-xx): ";

  std::string line;
  std::getline(std::cin, line);

  if (line.size() != 10)
    return std::unexpected("Invalid mapping! Please try again.");

  std::vector<std::string> possible_mappings{""};
  for (int i = 0; i < 10; i++) {
    if (line[i] == '?') {
      std::vector<std::string> new_mappings;
      for (std::string &mapping : possible_mappings) {
        new_mappings.push_back(mapping + ".");
        new_mappings.push_back(mapping + "-");
        new_mappings.push_back(mapping + "x");
      }
      possible_mappings = new_mappings;
    } else {
      for (std::string &mapping : possible_mappings)
        mapping += line[i];
    }
  }

  double confidence = 0.0;
  std::string output;
  for (std::string line : possible_mappings) {
    std::map<int, char> mapping;
    for (int i = 0; i < 10; i++)
      mapping[i] = line[i];

    std::string morse = "";
    for (char c : input)
      morse += mapping[c - '0'];

    auto decoded_message = MorseCode::decode(morse);
    if (!decoded_message)
      continue;

    if (English::probability(*decoded_message) > confidence) {
      confidence = English::probability(*decoded_message);
      output = *decoded_message;
    }
  }
  return output;
}