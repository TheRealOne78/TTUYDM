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
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <spdlog/spdlog.h>

User::User() { }

/* Setters */
void User::setName(const char* name) {
    std::strncpy(this->name, name, LOGIN_NAME_MAX);

    /* Ensure NULL terminator */
    this->name[LOGIN_NAME_MAX] = '\0';
}

void User::setUID(const uid_t uid) {
    this->uid = uid;
}

void User::setPasswd(const std::string passwd) {
    this->passwd = std::move(passwd);
}

void User::setHomePath(const char* home_path) {
    std::strncpy(this->home_path, home_path, PATH_MAX);

    /* Ensure NULL terminator */
    this->home_path[PATH_MAX] = '\0';
}

/* Getters */
const char* User::getName() const {
    return this->name;
}

const uid_t User::getUID() const {
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
    pam_handle_t* pamh = nullptr;

    /* Define the PAM conversation function using a lambda */
    struct pam_conv pam_conversation = {
    [](int num_msg,
       const struct pam_message** msg,
       struct pam_response** resp,
       void* appdata_ptr) -> int
    {
        /* check if num_msg is valid */
        if (num_msg <= 0)
            return PAM_CONV_ERR;

        struct pam_response* reply = (struct pam_response*)calloc(num_msg, sizeof(struct pam_response));

        /* check if we have a valid PAM response */
        if (reply == nullptr)
            return PAM_CONV_ERR;

        for (int i = 0; i < num_msg; ++i) {
            /* Password passed by appdata_ptr */
            reply[i].resp = strdup(static_cast<const char*>(appdata_ptr));

            if (reply[i].resp == nullptr) {

                for (int j = 0; j < i; ++j)
                    free(reply[j].resp);

                free(reply);

                return PAM_CONV_ERR;
            }

            reply[i].resp_retcode = 0;
        }

        *resp = reply;

        return PAM_SUCCESS;
    }, (void*)getPasswd().c_str() };

    int retval = pam_start("login", this->getName(), &pam_conversation, &pamh);

    if (retval != PAM_SUCCESS) {
        spdlog::error("pam_start failed: {}", pam_strerror(pamh, retval));

        return false;
    }

    retval = pam_authenticate(pamh, 0);
    if (retval != PAM_SUCCESS) {
        spdlog::error("pam_authenticate failed: {}", pam_strerror(pamh, retval));
        //spdlog::error("{}", this->getPasswd());
        //BUG: this->getPasswd() and this->passwd are always empty, even tho the setter is OK
        pam_end(pamh, retval);

        return false;
    }

    retval = pam_acct_mgmt(pamh, 0);
    if (retval != PAM_SUCCESS) {
        spdlog::error("pam_acct_mgmt failed: {}", pam_strerror(pamh, retval));
        pam_end(pamh, retval);

        return false;
    }

    pam_end(pamh, PAM_SUCCESS);

    return true;
}
