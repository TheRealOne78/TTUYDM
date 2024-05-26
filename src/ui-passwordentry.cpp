#include "ui-passwordentry.hpp"
#include <ncurses.h>
#include <stdexcept>
#include <sys/types.h>

PasswordEntry::PasswordEntry(WINDOW* win, int x, int y, uint16_t max_length)
  : win(win), x(x), y(y), max_length(max_length) {}

std::string& PasswordEntry::getPassword() {
  return this->password;
}

int PasswordEntry::handleInput() {
  int ch;
  while ((ch = wgetch(win)) != '\n') {
    if (ch == KEY_BACKSPACE || ch == 127) {
      if (!password.empty()) {
        password.pop_back();
      }
    }

    else if (ch == KEY_UP || ch== KEY_DOWN)
      return ch;

    else {
      // Calculate the maximum length of the password based on available space
      int max_password_length = max_length - 1; // Leave space for null terminator
      if (password.size() < max_password_length) {
        password.push_back(ch);
      }
    }
    display();
  }

  throw std::runtime_error("Unknown error");
}

void PasswordEntry::display() const {
  mvwprintw(win, y, x, "%s", std::string(max_length, ' ').c_str()); // Clear line

  for (uint64_t i = 0; i < password.size() || i < max_length; ++i) {
    attron(A_STANDOUT);
    mvwaddch(win, y, x + i, '*');
    attroff(A_STANDOUT);
  }
  wrefresh(win);
}
