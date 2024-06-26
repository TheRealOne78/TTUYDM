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

#ifndef __UI_SESSIONENTRY_HPP__
#define __UI_SESSIONENTRY_HPP__

#include "iui-entry.hpp"
#include <string>
#include <ncurses.h>
#include <vector>

class SessionEntry : public IUiEntry {
public:
    /* Constructors */
    SessionEntry(WINDOW* win,
                 uint16_t y, uint16_t x,
                 uint16_t max_length,
                 const std::vector<std::string>& sessions);

    /* Getters */
    std::string sessionName();

    int handleInput() override;
    void display() const override;

private:
    WINDOW* win;
    uint16_t x, y;
    uint16_t max_length;
    std::vector<std::string> sessions;
    uint64_t selectedIndex;
};

#endif // __UI_SESSIONENTRY_HPP__
