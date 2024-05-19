#include "ui.hpp"
#include <curses.h>

UI::UI() {

}

UI::~UI() {
    delwin(*top_bar_window);
    endwin();
}


void UI::drawHome(WINDOW*) {

}

void UI::drawHelp(WINDOW*) {

}

/* Bars */
void UI::drawHeaderBar(WINDOW*) {

}

void UI::drawFooterBar(WINDOW*) {

}

/* Windows */
void UI::drawWinCredentials(WINDOW*) {

}

void UI::drawTime(WINDOW*) {

}

void UI::drawPasswordFailedAttempts(WINDOW*) {

}

void UI::drawPasswordAttemptsUntillCooldown(WINDOW*) {

}

void UI::drawPasswordCooldown(WINDOW*) {

}
