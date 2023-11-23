#include <PolluxCipher.hpp>

#include <iostream>

auto main(int argc, char **argv) -> int {
  if (argc != 3) {
    std::cout << "Usage: pollux <encode|decode> <input>" << std::endl;
    return 0;
  }

  std::string mode{argv[1]};
  std::string input{argv[2]};

  if (mode == "encode") {
    std::cout << PolluxCipher::encode(input) << std::endl;
  } else if (mode == "decode") {
    std::cout << *PolluxCipher::decode(input) << std::endl;
  } else {
    std::cout << "Usage: pollux <encode|decode> <input>" << std::endl;
  }

  return 0;
}