#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono>
#include <thread>

// Utility function to split a string by a delimiter.
std::vector<std::string> split(const std::string& str, char delimiter);

// Utility function to trim whitespace from both ends of a string.
std::string trim(const std::string& str);

// Utility function to pause execution for a specified duration in milliseconds.
void sleep_for(int milliseconds);

#endif // UTILS_H