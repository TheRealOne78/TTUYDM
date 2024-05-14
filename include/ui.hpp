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
};

#endif // __UI_HPP__
