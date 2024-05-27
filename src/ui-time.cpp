#include "ui-time.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>

std::string getCurrentDateTime() {
    // Get current time
    auto now = std::chrono::system_clock::now();

    // Convert to time_t (seconds since epoch)
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert to struct tm
    std::tm localTime = *std::localtime(&currentTime);

    // Format date and time
    std::stringstream ss;
    ss << std::put_time(&localTime, "%Y/%m/%d - %I:%M:%S %p");

    return ss.str();
}
