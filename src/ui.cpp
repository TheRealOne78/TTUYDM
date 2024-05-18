#include "ui.hpp"
#include <curses.h>

UI::UI() {

}

UI::~UI() {
    delwin(top_bar_window);
    endwin();
}
