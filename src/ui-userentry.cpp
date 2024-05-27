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

#include "ui-userentry.hpp"

UserEntry::UserEntry(WINDOW* win, uint16_t y, uint16_t x, uint16_t maxLength, const std::vector<std::string>& users)
    : win(win), y(y), x(x), maxLength(maxLength), users(users), selectedIndex(0), active(false) {}

int UserEntry::handleInput() {
    int ch;
    while ((ch = wgetch(win)) != '\n') {
        if (active) {
            if (ch == KEY_BACKSPACE || ch == 127) {
                if (!input.empty()) {
                    input.pop_back();
                }
            } else if (input.size() < maxLength) {
                input.push_back(ch);
            }
        } else {
            switch (ch) {
                case KEY_LEFT:
                    if (selectedIndex > 0) {
                        --selectedIndex;
                    }
                    break;
                case KEY_RIGHT:
                    if (selectedIndex < users.size()) {
                        ++selectedIndex;
                    }
                    if (selectedIndex == users.size()) {
                        active = true;
                        input.clear();
                    }
                    break;
            }
        }
        display();
    }
}

void UserEntry::display() const {
    mvwprintw(win, y, x, "%s", std::string(maxLength, ' ').c_str()); // Clear line
    if (active) {
        mvwprintw(win, y, x, "%s", input.c_str());
    } else {
        mvwprintw(win, y, x, "%s", users[selectedIndex].c_str());
    }
    wrefresh(win);
}
