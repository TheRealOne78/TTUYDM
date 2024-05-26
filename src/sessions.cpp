#include "sessions.hpp"

Sessions::Sessions() {
  sessionNames.push_back("TTY");
  // NOTE: this will get entirely rewritten
}

std::vector<std::string> Sessions::getAllSessionNames() {
  return this->sessionNames;
}
