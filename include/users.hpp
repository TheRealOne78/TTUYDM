#ifndef __USERS_H__
#define __USERS_H__

/**
 * @brief Store and process all users.
 */
#include "user.hpp"
#include <climits>
#include <vector>
#include <pwd.h>

class Users {
    public:
        /* Constructors */
        Users();

        /* Deconstructors */
        ~Users();

        /* Setters */
        void addUserManuallyByName(const char [LOGIN_NAME_MAX]);

        /* Getters */
        User getUserByUID(const uid_t);
        User getUserByName(const char [LOGIN_NAME_MAX]);

        /* == Other methods == */
        void addUsersAuto();

    private:
        bool isNormalUser(const struct passwd*);
        std::vector<User>* users;
};

#endif // __USER_HPP__
