#pragma once
#include <deque>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadQueue {
    std::deque<T> q;
    std::mutex m;
    std::condition_variable cv;
public:
    void push(const T &v) {
        {
            std::lock_guard<std::mutex> lk(m);
            q.push_back(v);
        }
        cv.notify_all();
    }
    T wait_pop() {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [&]{ return !q.empty(); });
        T val = q.front();
        q.pop_front();
        return val;
    }
    bool try_pop(T &out) {
        std::lock_guard<std::mutex> lk(m);
        if (q.empty()) return false;
        out = q.front();
        q.pop_front();
        return true;
    }
    bool empty() {
        std::lock_guard<std::mutex> lk(m);
        return q.empty();
    }
    void notify_all() { cv.notify_all(); }
};
