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

#include "CppUTest/CommandLineTestRunner.h"

#include "users.hpp"
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <climits>
#include <termios.h>

static Users users;
char tmp_username[100];
uid_t tmp_uid;
char home_path[PATH_MAX];
std::string tmp_password;

TEST_GROUP(UserTests) {};

TEST(UserTests, CheckUserName) {
    STRCMP_EQUAL(users.getUserByName(tmp_username).getName(),
                 tmp_username);
}

TEST(UserTests, CheckUID) {
    CHECK(users.getUserByName(tmp_username).getUID() == tmp_uid);
}

TEST(UserTests, CheckHomePath) {
    STRCMP_EQUAL(home_path, users.getUserByName(tmp_username).getHomePath());
}

TEST(UserTests, CheckLogin) {
    CHECK(users.getUserByName(tmp_username).checkLogin());
}

void toggleEcho(bool enable) {
    // Made by ChatGPT
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);

    if (enable)
        tty.c_lflag |= ECHO;  // Enable echo
    else
        tty.c_lflag &= ~ECHO; // Disable echo

    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int main(int argc, char* argv[]) {
    /* == Prepare test file == */
    /* Set UI for test user */
    tmp_uid = getuid();

    /* Get info from the current user */
    struct passwd* pw = getpwuid(tmp_uid);

    /* Check if pw is not nullptr */
    if (pw == nullptr) {
        std::cerr << "Failed to get passwd struct for UID: " << tmp_uid << std::endl;
        abort();
    }

    /* Set home path and username for the test user */
    strcpy(home_path, pw->pw_dir);
    strcpy(tmp_username, pw->pw_name);

    /* Get password from user */
    std::string tmp_password;
    std::cout << "Please input login password for user '" << tmp_username << "' (one attempt only!): " << std::flush;
    toggleEcho(false);
    std::cin >> tmp_password;
    toggleEcho(true);

    /* Setup the test user */
    users.addUserManuallyByName(tmp_username);

    /* Add their password */
    users.getUserByName(tmp_username).setPasswd(tmp_password);


    /* == Run tests == */
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
