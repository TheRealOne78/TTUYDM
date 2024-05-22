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
        void drawHome();
        void drawHelp();
        /* Bars */
        void drawHeaderBar();
        void drawFooterBar();
        /* Windows */
        void drawWinCredentials();
        /* Requires */
        void drawTime(const WINDOW*);
        // |> requires user.hpp
        void drawPasswordFailedAttempts(const WINDOW*);
        void drawPasswordAttemptsUntilCooldown(const WINDOW*);
        void drawPasswordCooldown(const WINDOW*);

        void refreshMaxResolution();

        void wPrintWrap(const WINDOW*, const int, const int, const int, const char*);
        // <|

        /* == DATA == */
        int x_max, y_max;

        char* entered_password;
        uint64_t entered_password_length;

        // |> WINDOWS
        /* Bars */
        const WINDOW *TOP_BAR_WINDOW, *BOTTOM_BAR_WINDOW;

        /* Login entries */
        const WINDOW *ENTRIES_WINDOW;

        /* Help menu */
        const WINDOW *HELP_MENU_WINDOW;
        // <|

        /* Count of lines in the help menu */
        const uint8_t HELP_STR_LINES_COUNT;
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
