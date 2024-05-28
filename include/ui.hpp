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

#ifndef __UI_HPP__
#define __UI_HPP__

#include <curses.h>
#include <panel.h>
#include <string>
#include <vector>
#include <mutex>

#include "ui-userentry.hpp"
#include "ui-passwordentry.hpp"
#include "ui-sessionentry.hpp"

enum color_pairs {
_color_header = 1,
_color_warning,
_color_error
};

/**
 * @brief Handle everything related to the TUI
 */
class UI {
    public:
        /* == CONSTRUCTORS == */
        UI(std::vector<std::string> users, std::vector<std::string> sessions);

        /* == DECONSTRUCTORS == */
        ~UI();

        /* == METHODS == */

        /**
         * @brief Initiate text in the this->help_str STL vector
         *
         * @return None.
         */
        void initHelpStr();

        /* = Draw = */
        /* Screens */

        /**
         * @brief Write all the strings from the this->help_str STL vector in
         * the help window buffer.
         *
         * @return None.
         */
        void drawHelp();

        /* Bars */
        void drawHeaderBar();
        void drawFooterBar();
        /* Windows */
        void drawWinEntryCredentials();
        /* Requires */
        void drawTime();
        // |> requires user.hpp
        void drawPasswordFailedAttempts(WINDOW* win);


        /**
         * @brief Draw the PAM attempts until PAM user cooldown.
         *
         * @param win The window in which to print the Password Cooldown time
         *
         * @return None.
         */
        void drawPasswordAttemptsUntilCooldown(WINDOW* win);

        /**
         * @brief Draw the PAM password cooldown time in NCurses.
         *
         * Draw the PAM password cooldown time in NCurses in the specified WINDOW, at
         * the center.
         *
         * @param win The window in which to draw justify-center the Password Cooldown time
         *
         * @return None.
         */
        void drawPasswordCooldown(WINDOW* win);

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
        void refreshMaxResolution();


        /**
         * @brief Prints a string with wrapping in a window.
         *
         * This function prints the given string in the specified window, wrapping
         * the text to fit within the specified width.
         *
         * @note If the string contains newline characters ('\\n'), they are respected as
         * line breaks, unless the string contains only the newline character.
         *
         * @param win     The window to print in.
         * @param START_Y The y-coordinate of the starting position.
         * @param START_X The x-coordinate of the starting position.
         * @param WIDTH   The total width, in characters, to use in the window. Text
         *                will wrap to fit within this width.
         * @param STR     The string to print.
         *
         * @return None.
         */
        void wPrintWrap(WINDOW* win,
                        const uint16_t START_Y,
                        const uint16_t START_X,
                        const uint16_t WIDTH,
                        const char* STR);
        // <|

        int voidHandler();

        void initColorPairs();

    private:
        /* == DATA == */
        int x_max, y_max;

        char*    entered_password;
        uint64_t entered_password_length;

        // |> WINDOWS/PANELS
        /* Bars */
        WINDOW *top_bar_window, *bottom_bar_window;
        PANEL *top_bar_panel, *bottom_bar_panel;

        /* Login entries */
        WINDOW *entries_window;

        /* Help menu */
        WINDOW *help_menu_window;
        PANEL *help_menu_panel;
        // <|

        std::vector<std::string>* help_str;

        UserEntry     *user_entry;
        PasswordEntry *passwd_entry;
        SessionEntry  *session_entry;

        std::vector<std::string> users;
        std::vector<std::string> sessions;

        std::mutex mutex_update_panels;
};

#ifndef TOP_BAR_WINDOW_HEIGHT
# define TOP_BAR_WINDOW_HEIGHT 1    // no borders
#endif

#ifndef BOTTOM_BAR_WINDOW_HEIGHT
# define BOTTOM_BAR_WINDOW_HEIGHT 1 // no border
#endif

#ifndef ENTRIES_WINDOW_HEIGHT
# define ENTRIES_WINDOW_HEIGHT 9
#endif

#ifndef ENTRIES_WINDOW_WIDTH
# define ENTRIES_WINDOW_WIDTH 30
#endif


#ifndef mtx_upd
# define mtx_upd \
        mutex_update_panels.lock();  \
        update_panels();             \
        doupdate();                  \
        mutex_update_panels.unlock();
#endif /* mtx_upd */

#ifndef mtx_try_upd
# define mtx_try_upd \
        if (mutex_update_panels.try_lock()) {   \
                update_panels();                \
                doupdate();                     \
                mutex_update_panels.unlock();   \
        }
#endif /* mtx_try_upd */

#endif // __UI_HPP__
