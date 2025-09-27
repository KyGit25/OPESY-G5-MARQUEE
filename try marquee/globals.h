#pragma once
#include <atomic>
#include <string>
#include <mutex>
#include "ThreadQueue.h"

extern std::atomic<bool> exitFlag;
extern std::atomic<bool> runFlag;
extern std::atomic<int> marqueeSpeedMs;
extern std::string marqueeText;
extern std::mutex marqueeTextMutex;

extern ThreadQueue<std::string> displayQueue;
extern ThreadQueue<std::string> inputQueue;
