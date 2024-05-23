#ifndef __UI_HPP__
#define __UI_HPP__

#include <curses.h>
#include <string>
#include <vector>
#include "user.hpp"

class UI : public User {
    public:
        /* == CONSTRUCTORS == */
        UI();

        /* == DECONSTRUCTORS == */
        ~UI();

    private:
        /* == METHODS == */

        void initHelpStr();

        /* = Draw = */
        /* Screens */
        void drawHelp();
        /* Bars */
        void drawHeaderBar();
        void drawFooterBar();
        /* Windows */
        void drawWinEntryCredentials();
        /* Requires */
        void drawTime(WINDOW*);
        // |> requires user.hpp
        void drawPasswordFailedAttempts(WINDOW*);
        void drawPasswordAttemptsUntilCooldown(WINDOW*);
        void drawPasswordCooldown(WINDOW*);

        void refreshMaxResolution();

        void wPrintWrap(WINDOW*, const uint8_t, const uint8_t, const uint8_t, const char*);
        // <|

        /* == DATA == */
        int x_max, y_max;

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

        std::vector<std::string>* help_str;
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
