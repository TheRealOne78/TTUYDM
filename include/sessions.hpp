#ifndef __SESSIONS_HPP__
#define __SESSIONS_HPP__

#include <string>
#include <vector>
class Sessions {
  public:
    /* Constructors */
    Sessions();

    /* Deconstructors */

    /* Setters */


    /* Getters */
    std::vector<std::string> getAllSessionNames();


    /* Other methods */
  private:
    void addSessionsAuto();

    std::vector<std::string> sessionNames;

};

#endif // __SESSIONS_HPP__
