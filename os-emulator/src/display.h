#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display {
public:
    void showText(const std::string& text);
    void clearScreen();
    void updateMarquee(const std::string& marqueeText);
};

#endif // DISPLAY_H