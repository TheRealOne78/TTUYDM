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

#ifndef __USER_HPP__
#define __USER_HPP__

#include <cstdint>
#include <climits>
#include <linux/limits.h>
#include <string>
#include <pwd.h>

/**
 * @brief Store and process user credentials.
 *
 * This class stores, processes
 */
class User {
    public:
        /* Constructors */
        User();

        /* Deconstructors */
        ~User();

        /* Setters */
        void setName(const char*);
        void setUID(const uint64_t);
        void setPasswd(const std::string&);
        void setHomePath(const char*);

        /* Getters */
        const char* getName() const;
        const uint64_t getUID() const;
        const std::string& getPasswd() const;
        const char* getHomePath() const;

        /* == Other methods == */

        /**
         * @brief Check if the username is correct.
         *
         * @return True if correct, otherwise incorrect.
         */
        bool checkLogin();

    private:
        char name[LOGIN_NAME_MAX + 1];
        uint64_t uid;
        std::string passwd;
        char home_path[PATH_MAX + 1];
};

#endif // __USER_HPP__
