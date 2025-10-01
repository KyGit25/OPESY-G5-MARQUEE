#ifndef MARQUEE_H
#define MARQUEE_H

#include <string>
#include <atomic>
#include <thread>
#include <mutex>

class Marquee {
public:
    Marquee();
    ~Marquee();

    void start(const std::string& text, int speed);
    void stop();
    void update();

private:
    std::string marquee_text;
    int marquee_speed;
    std::atomic<bool> is_running;
    std::thread marquee_thread;
    std::mutex text_mutex;

    void marquee_logic();
};

#endif // MARQUEE_H