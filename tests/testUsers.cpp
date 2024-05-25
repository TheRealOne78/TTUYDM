#include "CppUTest/CommandLineTestRunner.h"

#include "users.hpp"
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <climits>

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

int main(int argc, char* argv[]) {
    tmp_uid = getuid();

    struct passwd* pw = getpwuid(tmp_uid);

    // Check if pw is not nullptr
    if (pw == nullptr)
        std::cerr << "Failed to get passwd struct for UID: " << tmp_uid << std::endl;
    strcpy(home_path, pw->pw_dir);
    strcpy(tmp_username, pw->pw_name);

    std::string tmp_password;
    std::cout << "Please input login password for user '" << tmp_username << "' (one attempt only!): ";
    std::cin >> tmp_password;

    users.addUserManuallyByName(tmp_username);
    users.getUserByName(tmp_username).setPasswd(tmp_password);

    return CommandLineTestRunner::RunAllTests(argc, argv);
}
