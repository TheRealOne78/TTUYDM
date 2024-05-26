#include "ui-userentry.hpp"

UserEntry::UserEntry(WINDOW* win, uint16_t y, uint16_t x, uint16_t maxLength, const std::vector<std::string>& users)
    : win(win), y(y), x(x), maxLength(maxLength), users(users), selectedIndex(0), active(false) {}

void UserEntry::handleInput() {
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
