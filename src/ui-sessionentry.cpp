#include "ui-sessionentry.hpp"
#include <ncurses.h>

SessionEntry::SessionEntry(WINDOW* win,
                           uint16_t y, uint16_t x,
                           uint16_t max_length,
                           const std::vector<std::string>& sessions)
  : win(win), y(y), x(x), max_length(max_length), sessions(sessions), selectedIndex(0) {}

void SessionEntry::handleInput() {
  int ch;
  while ((ch = wgetch(win)) != '\n') {
    switch (ch) {
      case KEY_RIGHT:
        selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : sessions.size() - 1;
        break;
      case KEY_LEFT:
        selectedIndex = (selectedIndex + 1) % sessions.size();
        break;
    }
    display();
  }
}

void SessionEntry::display() const {
  for (uint16_t i = 0; i < sessions.size(); ++i) {
    if (i == selectedIndex) {
      wattron(win, A_STANDOUT);
      mvwprintw(win, y, x, "%s", sessions[i].c_str());
      wattroff(win, A_STANDOUT);
    }
  }
  wrefresh(win);
}
