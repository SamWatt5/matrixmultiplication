#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point endTime;
    double timeElapsed = 0.0; // seconds

public:
    void startTimer();
    void endTimer();
    double getTime();
};