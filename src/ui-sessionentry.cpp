/*
 * Copyright (C) 2024 TheRealOne78 <bajcsielias78@gmail.com>
 *
 * This file is part of the TTUYDM project
 *
 * TTUYDM is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * TTUYDM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with TTUYDM. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "ui-sessionentry.hpp"
#include <ncurses.h>

SessionEntry::SessionEntry(WINDOW* win,
                           uint16_t y, uint16_t x,
                           uint16_t max_length,
                           const std::vector<std::string>& sessions)
  : win(win), y(y), x(x), max_length(max_length), sessions(sessions), selectedIndex(0) {}

int SessionEntry::handleInput() {
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
