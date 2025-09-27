#pragma once
#include <string>

class KeyboardHandler {
public:
    void run();
    static std::string getInput(const std::string &prompt);
};
