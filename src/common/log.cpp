#include "log.hpp"

#include <iostream>

namespace ABRUHP {
    void logError(std::string message) {
        std::cerr << "ERROR: " << message << std::endl;
        exit(EXIT_FAILURE);
    }
}