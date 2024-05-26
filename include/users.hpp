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
        /* == Constructors == */
        Users(void);

        /* == Deconstructors == */
        ~Users(void);

        /* == Setters == */
        /// Setter for adding manually a user.
        void addUserManuallyByName(const char [LOGIN_NAME_MAX]);

        /* == Getters == */
        /// Get a User by passing it's ID
        User getUserByUID(const uid_t);

        /// Get a User by passing it's username
        User getUserByName(const char [LOGIN_NAME_MAX]);

        /// Get all usernames by a vector of type std::string
        std::vector<std::string> getAllUsernames();

        /* == Other methods == */
        /**
         * @brief Automatically add all normal users.
         *
         * Add all normal users by searching and filtering out system POSIX users.
         *
         * @note Any users that have an UID less than 1000, are named `root` |
         * `daemon` | `nobody` or have their shells as
         * `/sbin/nologin` | `/bin/false` | `/sbin/halt` will be recognized as
         * system users.
         *
         * @return None.
         */
        void addUsersAuto(void);

    private:
        /**
         * @brief Check via passwd if a user is normal or not>
         *
         * Check whether or not a POSIX user is a system user or not.
         *
         * @note Any users that have an UID less than 1000, are named `root` |
         * `daemon` | `nobody` or have their shells as
         * `/sbin/nologin` | `/bin/false` | `/sbin/halt` will be recognized as
         * system users.
         *
         * @return True if normal user, false if system user.
         */
        bool isNormalUser(const struct passwd*);

        /// Store all users in a dynamic vector
        std::vector<User>* users;
};

#endif // __USER_HPP__
