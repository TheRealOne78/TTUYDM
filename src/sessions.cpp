#include "sessions.hpp"

Sessions::Sessions() {
  sessionNames.push_back("TTY");
}

std::vector<std::string> Sessions::getAllSessionNames() {
  return this->sessionNames;
}
