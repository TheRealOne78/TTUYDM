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
#include "ui-passwordentry.hpp"
#include <chrono>
#include <panel.h>
#include <string.h>
#include <curses.h>
#include <vector>
#include <spdlog/spdlog.h>
#include "ui-time.hpp"
#include <thread>

UI::UI(std::vector<std::string> users, std::vector<std::string> sessions)
    : users(users), sessions(sessions) {

    /* Start NCurses */
    initscr();

    /* Hide terminal cursor */
    if(! curs_set(0))
        spdlog::info("This virtual terminal doesn't support cursor hiding");

    if(noecho() != 0) {
        spdlog::error("Couldn't set terminal output to 'noecho'");
        exit(1);
    }

    /// TODO: Do this in the input handler
    //if (raw() != 0) {
    //    spdlog::error("Couldn't set terminal input to raw");
    //    exit(1);
    //}

    /* Initialize color pairs */
    this->initColorPairs();

    /* Get maximum  */
    this->refreshMaxResolution();

    /* Init all windows right now */
    this->top_bar_window    = newwin(TOP_BAR_WINDOW_HEIGHT, x_max, 0, 0);
    this->top_bar_panel     = new_panel(top_bar_window);

    this->bottom_bar_window = newwin(BOTTOM_BAR_WINDOW_HEIGHT,
                                     x_max,
                                     (y_max - BOTTOM_BAR_WINDOW_HEIGHT),
                                     0);
    this->bottom_bar_panel  = new_panel(bottom_bar_window);

    this->entries_window    = newwin(ENTRIES_WINDOW_HEIGHT,
                                     ENTRIES_WINDOW_WIDTH,
                                     ((y_max/2) - (ENTRIES_WINDOW_HEIGHT/2)),  /* center y */
                                     ((x_max/2) - (ENTRIES_WINDOW_HEIGHT/2))); /* center x */

    //TODO: Implement something more dynamic, like this
    //help_menu_window  = newwin((int)(y_max * .7f),                    /* 70% of y_max */
    //                           (int)(x_max * .7f),                    /* 70% of x_max */
    //                           ((y_max/2) - (int)(y_max * .7f / 2)),  /* center y */
    //                           ((x_max/2) - (int)(x_max * .7f / 2))); /* center x */

    this->help_menu_window  = newwin((int)(22),
                                     (int)(60),
                                     ((y_max/2) - (int)(22 / 2)),  /* center y */
                                     ((x_max/2) - (int)(60 / 2))); /* center x */
    this->help_menu_panel   = new_panel(help_menu_window);

    /*
     * Write help into memory immediatelly after the creation of
     * help_menu_window
     */
    this->initHelpStr();
    this->drawHelp();

    /* Write Header and Footer in memory */
    this->drawHeaderBar();
    this->drawFooterBar();

    /* Init entries */
    this->user_entry    = new UserEntry(entries_window    , 2, 2, ENTRIES_WINDOW_WIDTH - 4, users);
    this->passwd_entry  = new PasswordEntry(entries_window, 4, 2, ENTRIES_WINDOW_WIDTH - 4);
    this->session_entry = new SessionEntry(entries_window , 6, 2, ENTRIES_WINDOW_WIDTH - 4, sessions);

    ///* Draw header and footer onto screen  */
    mtx_try_upd

    while(1) {
        /* Temporary demo */
        // Wait for user input before hiding the window
        getch();

        // Hide the panel
        hide_panel(help_menu_panel);

        // Refresh to update the display
        mtx_upd

        // Wait for user input before showing the window again
        getch();

        // Show the panel (window)
        show_panel(help_menu_panel);

        // Refresh to update the display
        mtx_try_upd
    }
}

UI::~UI(void) {
    /* Delete all windows+panels */
    del_panel(top_bar_panel);
    delwin(top_bar_window);

    del_panel(bottom_bar_panel);
    delwin(bottom_bar_window);

    delwin(entries_window);

    del_panel(help_menu_panel);
    delwin(help_menu_window);

    /* delete entries */
    delete user_entry;
    delete passwd_entry;
    delete session_entry;

    /* End NCurses completely */
    endwin();
}


/*
 * TODO: Make the width size of the help menu proportional the size of the
 * longest string in this vector
 */
void UI::initHelpStr(void) {
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

void UI::drawHelp(void) {
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
void UI::drawHeaderBar(void) {
    /* Fill */
    wbkgd(this->top_bar_window, COLOR_PAIR(_color_header));

    std::thread time_date_thread([this]() { this->drawTime(); });
    time_date_thread.detach();
}

void UI::drawFooterBar(void) {
    wattron(bottom_bar_window , A_BOLD);
    mvwprintw(bottom_bar_window, 0, 0, "F1 - Help");
    wattroff(bottom_bar_window, A_BOLD);
}

void UI::drawTime() {
    /* Create temporary string to get the current time/date */
    std::string tmp_date_time;

    while (1) {
        /* Update current date and time in the string */
        tmp_date_time = getCurrentDateTime();


        attron(COLOR_PAIR(_color_header));
        /* Update the current date and time in the memory */
        mvwprintw(top_bar_window,
                  0, x_max - tmp_date_time.size(),
                  "%s", tmp_date_time.c_str());
        attroff(COLOR_PAIR(_color_header));

        /* update */
        mtx_try_upd

        /* Wait 150ms */
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void UI::drawPasswordFailedAttempts(WINDOW* win) {

    //TODO
}


void UI::drawPasswordAttemptsUntilCooldown(WINDOW* win) {

    //TODO
}

void UI::drawPasswordCooldown(WINDOW* win) {

    //TODO
}

void UI::refreshMaxResolution(void) {
    getmaxyx(stdscr, y_max, x_max);
}

void UI::wPrintWrap(WINDOW *win,
                const uint16_t START_Y,
                const uint16_t START_X,
                const uint16_t WIDTH,
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

void UI::initColorPairs() {
    if (!has_colors()) {
        spdlog::info("Terminal does not support colors");
        return;
    }

    start_color();
    use_default_colors();
    if (can_change_color()) {
        // Initialize true color support
        assume_default_colors(-1, -1);
    }

    init_pair(_color_header, COLOR_BLACK, COLOR_GREEN);

    init_pair(_color_warning, COLOR_YELLOW, -1);
    init_pair(_color_error, COLOR_RED, -1);
}
