#include "ui.hpp"
#include <string.h>
#include <curses.h>
#include <vector>

UI::UI() {
    /* Start NCurses */
    initscr();

    /* Get maximum  */
    refreshMaxResolution();

    /* Init all windows right now */
    top_bar_window    = newwin(TOP_BAR_WINDOW_HEIGHT, x_max, 0, 0);
    bottom_bar_window = newwin(BOTTOM_BAR_WINDOW_HEIGHT,
                               x_max,
                               (y_max - BOTTOM_BAR_WINDOW_HEIGHT),
                               0);

    entries_window    = newwin(ENTRIES_WINDOW_HEIGHT,
                               ENTRIES_WINDOW_WIDTH,
                               ((y_max/2) - (ENTRIES_WINDOW_HEIGHT/2)),
                               ((x_max/2) - (ENTRIES_WINDOW_HEIGHT/2)));

    help_menu_window  = newwin(
                               ((y_max/2) - (/2)),
                               ((x_max/2) - (/2)));
}

UI::~UI() {
    /* Delete all windows */
    delwin(top_bar_window);
    delwin(bottom_bar_window);
    delwin(entries_window);
    delwin(help_menu_window);

    /* End NCurses completely */
    endwin();
}

void UI::initHelpStr() {
    help_str->push_back((char*)"[KEYS]");
    help_str->push_back((char*)"ESC - Return to login screen");
    help_str->push_back((char*)"Arrow keys - Move between input entries");
    help_str->push_back((char*)"F1 - See this HELP menu");
    help_str->push_back((char*)"F12 - Reset all input entries");
    help_str->push_back((char*)"DEL - Reset selected input (also opposite to Ctrl+G)");
    help_str->push_back((char*)"Ctrl+G - Show last item");
    help_str->push_back((char*)"Ctrl+L - Login");
    help_str->push_back((char*)"\n");

    help_str->push_back((char*)"[BUTTONS]");
    help_str->push_back((char*)"Reset - Reset all input entries (same as F12)");
    help_str->push_back((char*)"Login - Login (Same as Ctrl+L)");
    help_str->push_back((char*)"\n");

    help_str->push_back((char*)"[ENTRIES]");
    help_str->push_back((char*)"USERNAME - Username credential");
    help_str->push_back((char*)"PASSWORD - Password credential");
    help_str->push_back((char*)"SESSION - The session to load after signing in");

}

void UI::drawHelp() {
    wPrintWrap(help_menu_window,
               getcury(help_menu_window) + 1,
               2,
               getmaxx(help_menu_window),
               str);
}

/* Bars */
void UI::drawHeaderBar() {

}

void UI::drawFooterBar() {

}

/* Windows */

void UI::drawTime(WINDOW* win) {

}

void UI::drawPasswordFailedAttempts(WINDOW* win) {

}

void UI::drawPasswordAttemptsUntilCooldown(WINDOW* win) {

}

/**
 * @brief Draw the PAM password cooldown time in NCurses.
 *
 * Draw the PAM password cooldown time in NCurses in the specified WINDOW, at
 * the center.
 *
 * @param window The window in which to draw justify-center the Password Cooldown time
 *
 * @return None.
 */
void UI::drawPasswordCooldown(WINDOW* win) {

}

/**
 * @brief Refresh the maximum resolution for ncurses standard screen
 *
 * Refresh the maximum resolution for ncurses standard screen.
 * This automatically updates UI::x_max and UI::y_max.
 *
 * This method is recommended to use because you don't have to type any
 * parameters.
 *
 * @return None.
 */
void UI::refreshMaxResolution() {
    getmaxyx(stdscr, x_max, y_max);
}


/**
 * @brief Print wrapped string in a window
 *
 * @param win The window to print in
 *
 * @param START_X The y start position
 *
 * @param START_X The x start position
 *
 * @param The total character width to use in the window. Customize with caution.
 *
 * @param STR The string to print
 *
 * @return None.
 */
void wPrintWrap(WINDOW *win,
                const int START_Y,
                const int START_X,
                const int WIDTH,
                const char* STR)
{
    int current_x = START_X;
    int current_y = START_Y;

    for (int i = 0; i < strlen(STR); i++) {
        /*
         * Check current width info for each itteration and update the y
         * position
         */
        if (current_x - START_X >= WIDTH || STR[i] == '\n') {
            current_y++;
            current_x = START_X;
        }

        /* Write char-by-char with newline constraint */
        if (STR[i] != '\n') {
            mvwaddch(win, current_y, current_x, STR[i]);
            current_x++;
        }
    }

    /* Render */
    refresh();
    wrefresh(win);
}
