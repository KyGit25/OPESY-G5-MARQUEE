#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

class Marquee {
public:
    Marquee() : is_running(false), speed(100), text("Welcome to the OS Emulator!") {}

    void start() {
        is_running = true;
        marquee_thread = std::thread(&Marquee::run, this);
    }

    void stop() {
        is_running = false;
        if (marquee_thread.joinable()) {
            marquee_thread.join();
        }
    }

    void setText(const std::string& new_text) {
        std::lock_guard<std::mutex> lock(text_mutex);
        text = new_text;
    }

    void setSpeed(int new_speed) {
        std::lock_guard<std::mutex> lock(speed_mutex);
        speed = new_speed;
    }

private:
    void run() {
        while (is_running) {
            {
                std::lock_guard<std::mutex> lock(text_mutex);
                std::cout << "\r" << text << std::flush;
                text = text.substr(1) + text[0]; // Rotate text
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
        std::cout << std::endl; // Clear line after stopping
    }

    std::atomic<bool> is_running;
    std::thread marquee_thread;
    std::mutex text_mutex;
    std::mutex speed_mutex;
    std::string text;
    int speed;
};