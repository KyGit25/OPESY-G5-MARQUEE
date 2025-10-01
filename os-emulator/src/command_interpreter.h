#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string>
#include "marquee.h"
#include "display.h"

class CommandInterpreter {
public:
    CommandInterpreter(Display& display, Marquee& marquee);
    void processCommand(const std::string& command);
    void showHelp();

private:
    Display& display;
    Marquee& marquee;

    void startMarquee(const std::string& text, int speed);
    void stopMarquee();
    void setText(const std::string& text);
    void setSpeed(int speed);
};

#endif // COMMAND_INTERPRETER_H