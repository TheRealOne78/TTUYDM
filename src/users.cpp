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

void Users::addUsersAuto() {

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

            delete tmp_user;
        }
    }

    /* Close passwd db */
    endpwent();
}

void Users::addUserManuallyByName(const char NAME[LOGIN_NAME_MAX]) {

    /* Rewind the passwd db */
    setpwent();

    struct passwd* tmp_passwd;
    bool hasAdded = false;

    while ((tmp_passwd = getpwent()) != nullptr) {
        if (strcmp(tmp_passwd->pw_name, NAME) == 0) {
            if(! isNormalUser(tmp_passwd))
                throw "specified user is not normal";

            User *tmp_user = new User;

            tmp_user->setName(tmp_passwd->pw_name);
            tmp_user->setUID(tmp_passwd->pw_uid);
            tmp_user->setHomePath(tmp_passwd->pw_dir);

            users->push_back(*tmp_user);

            delete tmp_user;

            hasAdded = true;

            break;
        }
    }

    /* Close passwd db */
    endpwent();

    if(!hasAdded)
        throw "specified user cannot be found";
}

/* Getters */
User Users::getUserByUID(const uid_t UID) {
    for(User user : *this->users) {
        if(user.getUID() == UID)
            return user;
    }

    throw "User does not exist";
}


User Users::getUserByName(const char NAME[LOGIN_NAME_MAX]) {
    for(User user : *this->users) {
        if(strcmp(user.getName(), NAME) == 0)
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
