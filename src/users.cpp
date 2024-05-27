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

#include "users.hpp"
#include <stdexcept>
#include <string.h>
#include <vector>

Users::Users(void) {
    this->users = new std::vector<User>;

    /* Initiate all users */
    this->addUsersAuto();
}

Users::~Users(void) {
    /* Destroy this->users */
    this->users->clear();
    delete this->users;
}

void Users::addUserManuallyByName(const char NAME[LOGIN_NAME_MAX]) {

    /* Rewind the passwd db */
    setpwent();

    struct passwd* tmp_passwd;
    bool hasAdded = false;

    while ((tmp_passwd = getpwent()) != nullptr) {
        if (strcmp(tmp_passwd->pw_name, NAME) == 0) {
            //if(! isNormalUser(tmp_passwd))
            //    throw std::runtime_error("specified user is not normal");
            //FIXME:TODO: remove this because one would add this user only if it wasn't normal?

            User tmp_user;

            tmp_user.setName(tmp_passwd->pw_name);
            tmp_user.setUID(tmp_passwd->pw_uid);
            tmp_user.setHomePath(tmp_passwd->pw_dir);

            users->push_back(tmp_user);

            hasAdded = true;

            break;
        }
    }

    /* Close passwd db */
    endpwent();

    if(!hasAdded)
        throw std::runtime_error("The specified user cannot be found.");
}

/* Getters */
User Users::getUserByUID(const uid_t UID) {
    for(User user : *this->users) {
        if(user.getUID() == UID)
            return user;
    }
    throw std::runtime_error("This user does not exist");
}

User Users::getUserByName(const char NAME[LOGIN_NAME_MAX]) {
    for(User user : *this->users) {
        if(strcmp(user.getName(), NAME) == 0)
            return user;
    }

    throw std::runtime_error("This user does not exist");
}


std::vector<std::string> Users::getAllUsernames() {
    std::vector<std::string> tmp;

    for(User user : *this->users)
        tmp.push_back(std::string(user.getName()));

    return tmp;
}

/* Other methods */

void Users::addUsersAuto(void) {

    /* Rewind the passwd db */
    setpwent();

    struct passwd* tmp_passwd;

    while ((tmp_passwd = getpwent()) != nullptr) {
        if (isNormalUser(tmp_passwd)) {
            User *tmp_user = new User;

            tmp_user->setName(tmp_passwd->pw_name);
            tmp_user->setUID(tmp_passwd->pw_uid);
            tmp_user->setHomePath(tmp_passwd->pw_dir);

            users->push_back(*tmp_user);

            //delete tmp_user;
        }
    }

    /* Close passwd db */
    endpwent();
}

bool Users::isNormalUser(const struct passwd* pwd) {
    /* Exclude users with UID below 1000 */
    if (pwd->pw_uid < 1000)
        return false;

    /* Exclude system users */
    if (std::string(pwd->pw_name) == "root"   ||
        std::string(pwd->pw_name) == "daemon" ||
        std::string(pwd->pw_name) == "nobody")
    {
        return false;
    }

    /* Exclude users with system shells */
    if (std::string(pwd->pw_shell) == "/sbin/nologin" ||
        std::string(pwd->pw_shell) == "/bin/false"    ||
        std::string(pwd->pw_shell) == "/sbin/halt")
    {
        return false;
    }

    return true;
}
