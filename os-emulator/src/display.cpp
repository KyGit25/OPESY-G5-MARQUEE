#include "display.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

Display::Display() : marquee_text(""), marquee_speed(100), is_marquee_running(false) {}

void Display::setMarqueeText(const std::string& text) {
    std::lock_guard<std::mutex> lock(mutex_);
    marquee_text = text;
}

void Display::setMarqueeSpeed(int speed) {
    std::lock_guard<std::mutex> lock(mutex_);
    marquee_speed = speed;
}

void Display::startMarquee() {
    is_marquee_running = true;
    marquee_thread = std::thread(&Display::runMarquee, this);
}

void Display::stopMarquee() {
    is_marquee_running = false;
    if (marquee_thread.joinable()) {
        marquee_thread.join();
    }
}

void Display::runMarquee() {
    while (is_marquee_running) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!marquee_text.empty()) {
                std::cout << "\r" << std::setw(40) << std::setfill(' ') << marquee_text << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(marquee_speed));
                marquee_text = marquee_text.substr(1) + marquee_text[0]; // Rotate text
            }
        }
    }
    std::cout << std::endl; // Move to the next line after stopping
}

void Display::clear() {
    std::cout << "\033[2J\033[1;1H"; // Clear console and move cursor to top-left
}

Display::~Display() {
    stopMarquee();
}