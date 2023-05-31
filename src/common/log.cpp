#include "log.hpp"

#include <iostream>

namespace ABRUHP {
void logError(std::string message) {
  std::cerr << "ERROR: " << message << std::endl;
  exit(EXIT_FAILURE);
}

void logError(std::string message, size_t line) {
  std::cerr << "ERROR on line " << line << ": " << message  << std::endl;
  exit(EXIT_FAILURE);
}
} // namespace ABRUHP