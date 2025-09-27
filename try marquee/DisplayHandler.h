#pragma once
#include <string>
#include <mutex>

class DisplayHandler {
public:
    void run();
    static void show(const std::string &message);
private:
    static std::mutex ioMutex;
    void printMessage(const std::string &m);
};
