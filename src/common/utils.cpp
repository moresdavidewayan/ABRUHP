#include "utils.hpp"

#include <fstream>

#include "log.hpp"

std::string readFile(std::string path) {
  std::string result;

  std::ifstream file(path);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      result += line;
      result.push_back('\n');
    }
  } else
    logError("Cannot read file.");

  return result;
}