#include "command_interpreter.h"
#include <iostream>
#include <string>
#include <sstream>
#include "marquee.h"
#include "display.h"

class CommandInterpreter {
public:
    CommandInterpreter(Display& display, Marquee& marquee)
        : display(display), marquee(marquee) {}

    void process_command(const std::string& command) {
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "help") {
            display.show_help();
        } else if (cmd == "start_marquee") {
            marquee.start();
        } else if (cmd == "stop_marquee") {
            marquee.stop();
        } else if (cmd == "set_text") {
            std::string text;
            std::getline(iss, text);
            marquee.set_text(text);
        } else if (cmd == "set_speed") {
            int speed;
            iss >> speed;
            marquee.set_speed(speed);
        } else if (cmd == "exit") {
            exit_program();
        } else {
            display.show_error("Unknown command: " + command);
        }
    }

private:
    Display& display;
    Marquee& marquee;

    void exit_program() {
        display.show_message("Exiting the OS emulator...");
        // Additional cleanup if necessary
        std::exit(0);
    }
};