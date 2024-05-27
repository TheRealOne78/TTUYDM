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

#ifndef __UI_PASSWORDENTRY_HPP__
#define __UI_PASSWORDENTRY_HPP__

#include "iui-entry.hpp"
#include <string>
#include <ncurses.h>

class PasswordEntry : public IUiEntry {
    public:
        PasswordEntry(WINDOW* win,
                      int x, int y,
                      uint16_t max_length);

        /* Getters */
        std::string& getPassword();

        int handleInput() override;
        void display() const override;

    private:
        WINDOW* win;
        int x, y, max_length;
        std::string password;
};

#endif // __UI_PASSWORDENTRY_HPP__
