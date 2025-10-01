#include "utils.h"
#include <string>
#include <chrono>
#include <thread>

// Utility function to trim whitespace from both ends of a string.
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return ""; // No content
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Utility function to pause execution for a specified duration in milliseconds.
void sleep_for(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}