#pragma once

#include <string>

namespace ABRUHP {
void logError(std::string message);

void logError(std::string message, size_t line);
}