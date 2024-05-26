#ifndef __UI_SESSIONENTRY_HPP__
#define __UI_SESSIONENTRY_HPP__

#include "iui-entry.hpp"
#include <string>
#include <ncurses.h>
#include <vector>

class SessionEntry : public IUiEntry {
public:
    /* Constructors */
    SessionEntry(WINDOW* win,
                 uint16_t y, uint16_t x,
                 uint16_t max_length,
                 const std::vector<std::string>& sessions);

    /* Getters */
    std::string sessionName();

    int handleInput() override;
    void display() const override;

private:
    WINDOW* win;
    uint16_t x, y;
    uint16_t max_length;
    std::vector<std::string> sessions;
    uint64_t selectedIndex;
};

#endif // __UI_SESSIONENTRY_HPP__
