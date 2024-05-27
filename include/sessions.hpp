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

#ifndef __SESSIONS_HPP__
#define __SESSIONS_HPP__

#include <string>
#include <vector>
class Sessions {
    public:
        /* Constructors */
        Sessions();

        /* Deconstructors */

        /* Setters */


        /* Getters */
        std::vector<std::string> getAllSessionNames();


        /* Other methods */
    private:
        void addSessionsAuto();

        std::vector<std::string> sessionNames;

};

#endif // __SESSIONS_HPP__
