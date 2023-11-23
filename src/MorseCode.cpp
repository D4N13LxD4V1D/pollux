#include <MorseCode.hpp>

#include <map>

std::map<char, std::string> morse_map_encode{
    {'a', ".-"},    {'b', "-..."},  {'c', "-.-."},  {'d', "-.."},
    {'e', "."},     {'f', "..-."},  {'g', "--."},   {'h', "...."},
    {'i', ".."},    {'j', ".---"},  {'k', "-.-"},   {'l', ".-.."},
    {'m', "--"},    {'n', "-."},    {'o', "---"},   {'p', ".--."},
    {'q', "--.-"},  {'r', ".-."},   {'s', "..."},   {'t', "-"},
    {'u', "..-"},   {'v', "...-"},  {'w', ".--"},   {'x', "-..-"},
    {'y', "-.--"},  {'z', "--.."},  {'1', ".----"}, {'2', "..---"},
    {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."},
    {'7', "--..."}, {'8', "---.."}, {'9', "----."}, {'0', "-----"},
    {' ', ""}};

std::map<std::string, char> morse_map_decode{
    {".-", 'a'},    {"-...", 'b'},  {"-.-.", 'c'},  {"-..", 'd'},
    {".", 'e'},     {"..-.", 'f'},  {"--.", 'g'},   {"....", 'h'},
    {"..", 'i'},    {".---", 'j'},  {"-.-", 'k'},   {".-..", 'l'},
    {"--", 'm'},    {"-.", 'n'},    {"---", 'o'},   {".--.", 'p'},
    {"--.-", 'q'},  {".-.", 'r'},   {"...", 's'},   {"-", 't'},
    {"..-", 'u'},   {"...-", 'v'},  {".--", 'w'},   {"-..-", 'x'},
    {"-.--", 'y'},  {"--..", 'z'},  {".----", '1'}, {"..---", '2'},
    {"...--", '3'}, {"....-", '4'}, {".....", '5'}, {"-....", '6'},
    {"--...", '7'}, {"---..", '8'}, {"----.", '9'}, {"-----", '0'},
};

auto MorseCode::encode(std::string input) -> std::string {
  std::string output = "";
  for (char c : input)
    output += morse_map_encode[tolower(c)] + "x";

  return output;
}

auto MorseCode::decode(std::string input)
    -> std::expected<std::string, std::string> {
  std::string output = "";
  std::string current = "";
  for (int i = 0; i < input.length(); i++) {
    char c = input[i];
    if (c == 'x') {
      if (morse_map_decode.find(current) == morse_map_decode.end())
        return std::unexpected("Invalid morse code");

      output += morse_map_decode[current];
      current = "x";

      while (i + 1 < input.length() && input[i + 1] == 'x') {
        current += input[i];
        i++;
      }

      if (current.length() > 2)
        return std::unexpected("Invalid space");
      else if (current.length() == 2)
        output += " ";

      current = "";
    } else {
      current += c;
    }
  }

  if (current != "") {
    if (morse_map_decode.find(current) == morse_map_decode.end())
      return std::unexpected("Invalid morse code");

    output += morse_map_decode[current];
  }

  return output;
}