#ifndef __UI_PASSWORDENTRY_HPP__
#define __UI_PASSWORDENTRY_HPP__

#include "iui-entry.hpp"
#include <string>
#include <ncurses.h>

class PasswordEntry : public IUiEntry {
  public:
    PasswordEntry(WINDOW* win,
                  int x, int y,
                  uint16_t max_length);

    /* Getters */
    std::string& getPassword();

    int handleInput() override;
    void display() const override;

  private:
    WINDOW* win;
    int x, y, max_length;
    std::string password;
};

#endif // __UI_PASSWORDENTRY_HPP__
