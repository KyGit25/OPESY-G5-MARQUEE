#include <iostream>
#include <thread>
#include <atomic>
#include "command_interpreter.h"
#include "menu.h"

// Global flag to control the running state of the application.
std::atomic<bool> is_running{true};

// Main function - entry point of the OS emulator.
int main() {
    CommandInterpreter command_interpreter;
    Menu menu;

    // Start the main menu loop.
    while (is_running) {
        menu.display();
        std::string command = menu.get_user_input();
        command_interpreter.process_command(command, is_running);
    }

    return 0;
}