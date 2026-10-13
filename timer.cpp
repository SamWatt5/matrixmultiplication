#include "timer.h"

void Timer::startTimer() {
    startTime = std::chrono::steady_clock::now();
}

void Timer::endTimer() {
    endTime = std::chrono::steady_clock::now();
    timeElapsed = std::chrono::duration<double>(endTime - startTime).count();
}

double Timer::getTime() {
    return timeElapsed;
}