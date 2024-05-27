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

#ifndef __UI_USERENTRY_HPP__
#define __UI_USERENTRY_HPP__

#include "iui-entry.hpp"
#include <string>
#include <ncurses.h>
#include <vector>

class UserEntry : public IUiEntry {
    public:
        UserEntry(WINDOW* win,
                  uint16_t y, uint16_t x,
                  uint16_t maxLength,
                  const std::vector<std::string>& users);

        int handleInput() override;
        void display() const override;

    private:
        WINDOW* win;
        int x, y, maxLength;
        std::string input;
        std::vector<std::string> users;
        uint64_t selectedIndex;
        bool active;
};

#endif // __UI_USERENTRY_HPP__
