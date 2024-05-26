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
 * @brief Store, get and process POSIX user's information.
 *
 * Store, get and process a POSIX user's information regarding their username,
 * user ID, the provided password and their home path.
 */
class User {
    public:
        /* == Constructors == */
        User();

        /* == Setters == */
        /// Setter for the user's name
        void setName(const char*);

        /// Setter for the user's ID
        void setUID(const uid_t);

        /// Setter for setting the password
        void setPasswd(const std::string&);

        /// Setter for the user's home path
        void setHomePath(const char*);

        /* == Getters == */
        /// Getter for user's name
        const char* getName(void) const;

        /// Getter for user's ID
        const uid_t getUID(void) const;

        /// Getter for the provided password
        const std::string& getPasswd(void) const;

        /// Getter for the user home path
        const char* getHomePath(void) const;

        /* == Other methods == */
        /**
         * @brief Check if user can authenticate with the current credentials.
         *
         * Check if the user can authenticate via /etc/pam.d/login with the
         * provided credentials.
         *
         * @return True if the credentials are correct, otherwise false if
         * incorrect credentials.
         */
        bool checkLogin(void);

    private:
        char name[LOGIN_NAME_MAX + 1]; /* +1 for NULL terminator */
        uint64_t uid;
        std::string* passwd;
        char home_path[PATH_MAX + 1];  /* +1 for NULL terminator */
};

#endif // __USER_HPP__
