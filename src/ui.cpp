#include "ui.hpp"
#include <curses.h>

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


void UI::drawHome() {

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
void UI::drawWinCredentials() {

}

void UI::drawTime(WINDOW*) {

}

void UI::drawPasswordFailedAttempts(WINDOW*) {

}

void UI::drawPasswordAttemptsUntilCooldown(WINDOW*) {

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
void UI::drawPasswordCooldown(WINDOW* window) {

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
 * @param WIN The window to print in
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
void wPrintWrap(const WINDOW *WIN,
                const int START_Y,
                const int START_X,
                const int WIDTH,
                const char* STR)
{
    int current_x = START_X;
    int current_y = START_Y;

    for (int i = 0; i < strlen(STR); i++) {
        if (current_x - START_X >= WIDTH || STR[i] == '\n') {
            current_y++;
            current_x = START_X;
        }

        if (str[i] != '\n') {
            mvwaddch(WIN, current_y, current_x, STR[i]);
            current_x++;
        }
    }
    wrefresh(WIN);
}
