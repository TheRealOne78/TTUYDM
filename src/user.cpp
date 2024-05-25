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

#include "user.hpp"
#include <cstring>
#include <cstdint>

User::User() {

    //TODO
}

/* Deconstructors */
User::~User() {

    //TODO
}

/* Setters */
void User::setName(const char* name) {
    std::strncpy(this->name, name, LOGIN_NAME_MAX);

    /* Ensure NULL terminator */
    this->name[LOGIN_NAME_MAX] = '\0';
}

void User::setUID(const uint64_t uid) {
    this->uid = uid;
}

void User::setPasswd(const std::string& passwd) {
    this->passwd = passwd;
}

void User::setHomePath(const char* homePath) {
    std::strncpy(this->home_path, homePath, PATH_MAX - 1);

    /* Ensure NULL terminator */
    this->home_path[PATH_MAX] = '\0';
}

/* Getters */
const char* User::getName() const {
    return this->name;
}

const uint64_t User::getUID() const {
    return this->uid;
}

const std::string& User::getPasswd() const {
    return this->passwd;
}

const char* User::getHomePath() const {
    return this->home_path;
}

/* == Other methods == */

bool User::checkLogin() {
    //TODO
    return true;
}
