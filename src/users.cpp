#include "users.hpp"
#include <string.h>
#include <vector>


Users::Users() {
    this->users = new std::vector<User>;
}

Users::~Users() {
    /* Destroy this->users */
    this->users->clear();
    delete this->users;
}

void Users::addUserManuallyByName(const char* [LOGIN_NAME_MAX]) {

    /* Rewind the passwd db */
    setpwent();

    struct passwd* tmp_passwd;

    while ((tmp_passwd = getpwent()) != nullptr) {
        if (isNormalUser(tmp_passwd)) {
            User *tmp_user = new User;

            tmp_user->setName(tmp_passwd->pw_name);
            tmp_user->setUID(tmp_passwd->pw_uid);

            users->push_back(*tmp_user);

            delete tmp_user;
        }
    }

    /* Close passwd db */
    endpwent();
}

/* Getters */
User Users::getUserByUID(const uint64_t UID) {
    for(User user : *this->users) {
        if(user.getUID() == UID)
            return user;
    }

    throw "User does not exist";
}

User Users::getUserByName(const char* NAME[LOGIN_NAME_MAX]) {
    for(User user : *this->users) {
        if(strcmp(user.getName(), *NAME))
            return user;
    }

    throw "User does not exist";
}

/**
 * @brief Check if the user is normal.
 *
 * Check if the user is a normal user. This involves checking common system-user
 * patterns and then excluding them.
 *
 * @return True if correct, otherwise incorrect.
 */

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
