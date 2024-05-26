#ifndef __UI_USERENTRY_HPP__
#define __UI_USERENTRY_HPP__

#include "iui-entry.hpp"
#include <string>
#include <ncurses.h>
#include <vector>

class UserEntry : public IUiEntry {
public:
    UserEntry(WINDOW* win,
              uint16_t y, uint16_t x,
              uint16_t maxLength,
              const std::vector<std::string>& users);

    int handleInput() override;
    void display() const override;

private:
    WINDOW* win;
    int x, y, maxLength;
    std::string input;
    std::vector<std::string> users;
    uint64_t selectedIndex;
    bool active;
};

#endif // __UI_USERENTRY_HPP__
