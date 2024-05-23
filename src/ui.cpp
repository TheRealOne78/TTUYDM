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

#include "ui.hpp"
#include <string.h>
#include <curses.h>
#include <vector>
#include <spdlog/spdlog.h>

UI::UI() {
    /* Start NCurses */
    initscr();

    /* Hide terminal cursor */
    if(! curs_set(0))
        spdlog::info("This virtual terminal doesn't support cursor hiding");

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
                               ((y_max/2) - (ENTRIES_WINDOW_HEIGHT/2)),  /* center y */
                               ((x_max/2) - (ENTRIES_WINDOW_HEIGHT/2))); /* center x */

    //TODO: Implement something more dynamic, like this
    //help_menu_window  = newwin((int)(y_max * .7f),                    /* 70% of y_max */
    //                           (int)(x_max * .7f),                    /* 70% of x_max */
    //                           ((y_max/2) - (int)(y_max * .7f / 2)),  /* center y */
    //                           ((x_max/2) - (int)(x_max * .7f / 2))); /* center x */

    help_menu_window  = newwin((int)(22),
                               (int)(60),
                              ((y_max/2) - (int)(22 / 2)),  /* center y */
                               ((x_max/2) - (int)(60 / 2))); /* center x */

    /*
     * Write help into memory immediatelly after the creation of
     * help_menu_window
     */
    this->initHelpStr();
    this->drawHelp();
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


/**
 * @brief Initiate text in the this->help_str STL vector
 *
 * @return None.
 */
void UI::initHelpStr() {
    /* Create and assign a new dynamic STL vector */
    this->help_str = new std::vector<std::string>();

    /* Write help strings in the help_str vector */
    this->help_str->push_back("[ KEYS ]");
    this->help_str->push_back("<ESC> - Return to login screen");
    this->help_str->push_back("Arrow keys - Move between input entries");
    this->help_str->push_back("<F1> - See this HELP menu");
    this->help_str->push_back("<F12> - Reset all input entries");
    this->help_str->push_back("<DEL> - Reset selected input (also opposite to Ctrl+G)");
    this->help_str->push_back("<Ctrl+G> - Show last item");
    this->help_str->push_back("<Ctrl+L> - Login");

    this->help_str->push_back("\n[ BUTTONS ]");
    this->help_str->push_back("Reset - Reset all input entries (same as F12)");
    this->help_str->push_back("Login - Login (Same as Ctrl+L)");

    this->help_str->push_back("\n[ ENTRIES ]");
    this->help_str->push_back("USERNAME - Username credential");
    this->help_str->push_back("PASSWORD - Password credential");
    this->help_str->push_back("SESSION - The session to load after signing in");
}


/**
 * @brief Write all strings from this->help_str in the help window buffer
 *
 * Write all the strings from the this->help_str STL vector in the help window
 * buffer.
 *
 * @return None.
 */
void UI::drawHelp() {
    /* Print teh box borders */
    box(this->help_menu_window,
        0, 0);

    /* Print Help title */
    mvwprintw(this->help_menu_window,
              0, 2,
              "Help");

    /* Start position */
    wmove(this->help_menu_window, 1, 2);

    /* Print every line from the this->wPrintWrap vector */
    for (const std::string& str : *this->help_str) {
        this->wPrintWrap(this->help_menu_window,
                         getcury(help_menu_window) + 1,
                         2,
                         getmaxx(help_menu_window),
                         str.c_str());
    }
}

/* Bars */
void UI::drawHeaderBar() {

    //TODO
}

void UI::drawFooterBar() {

    //TODO
}

/* Windows */

void UI::drawTime(WINDOW* win) {

    //TODO
}

void UI::drawPasswordFailedAttempts(WINDOW* win) {

    //TODO
}


/**
 * @brief Draw the PAM attempts until PAM user cooldown.
 *
 * @param window The window in which to print the Password Cooldown time
 *
 * @return None.
 */
void UI::drawPasswordAttemptsUntilCooldown(WINDOW* win) {

    //TODO
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

    //TODO
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
    getmaxyx(stdscr, y_max, x_max);
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
void UI::wPrintWrap(WINDOW *win,
                const uint8_t START_Y,
                const uint8_t START_X,
                const uint8_t WIDTH,
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
}
