#pragma once
#include <string>

class CommandInterpreter {
public:
    void run();
private:
    void showHelp();
    static void trim(std::string &s);
};
