#ifndef __UI_HPP__
#define __UI_HPP__

#include <curses.h>
#include "user.hpp"

class UI : public User {
    public:
        /* == CONSTRUCTORS == */
        UI();

        /* == DECONSTRUCTORS == */
        ~UI();

    private:
        /* == METHODS == */

        /* = Draw = */
        /* Screens */
        void drawHome(WINDOW*);
        void drawHelp(WINDOW*);
        /* Bars */
        void drawHeaderBar(WINDOW*);
        void drawFooterBar(WINDOW*);
        /* Windows */
        void drawWinCredentials(WINDOW*);
        /* Requires */
        void drawTime(WINDOW*);
        // |> requires user.hpp
        void drawPasswordFailedAttempts(WINDOW*);
        void drawPasswordAttemptsUntillCooldown(WINDOW*);
        void drawPasswordCooldown(WINDOW*);
        // <|

        /* == DATA == */
        int x_max, y_max;
        int x_current_pos, y_curent_pos;

        char* entered_password;
        uint64_t entered_password_length;

        // |> WINDOWS
        /* Bars */
        WINDOW *top_bar_window, *bottom_bar_window;

        /* Login entries */
        WINDOW *entries_window;

        /* Help menu */
        WINDOW *help_menu_window;
        // <|
};

#ifndef TOP_BAR_WINDOW_HEIGHT
# define TOP_BAR_WINDOW_HEIGHT 2    // two borders
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

#endif // __UI_HPP__
