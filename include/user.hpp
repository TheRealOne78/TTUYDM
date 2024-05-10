#ifndef __USER_HPP__
#define __USER_HPP__

#include <climits>

/**
 * @brief Store and process user credentials.
 *
 * This class stores, processes
 */
class User {
    public:
        /* Constructors */
        User();

        /* Deconstructors */
        ~User();

        /* Setters */
        void set_passwd();

        /* Getters */
        char* get_name();
        char* get_passwd();
        char* get_home_path();

        /* == Other methods == */

        /**
         * @brief Check if the username is correct.
         *
         * @return True if correct, otherwise incorrect.
         */
        bool check_username();

        /**
         * @brief Check if the username is correct.
         *
         * @return True if correct, otherwise incorrect.
         */
        bool check_login();

    private:
        char name[LOGIN_NAME_MAX];
        char* passwd;

        /* For check_user_normal() */
        bool has_home;
        bool has_normal_UID;
        bool has_normal;

        /**
         * @brief Check if the user is normal.
         *
         * Check if the user is a normal user. This involves looking at
         * `/etc/passwd' and see if the user has a home path and it's User ID
         * (UID) is greater or equal to 1000.
         *
         * NOTE:TODO: This approach might not work for all valid users, and
         * there might be a better approach.
         *
         * @return True if correct, otherwise incorrect.
         */
        bool check_user_normal();

        /**
         * @brief Check if the password is correct.
         *
         * Check if the password is correct with Pluggable Authentication
         * Modules (PAM).
         *
         * @return True if correct, otherwise incorrect.
         */
        bool check_password();

};

#endif // __USER_HPP__
