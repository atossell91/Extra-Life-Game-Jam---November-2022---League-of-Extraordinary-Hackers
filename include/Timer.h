//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include <functional>
#include <thread>

class Timer {
 private:
    bool shouldStop = false;
    std::thread* t;
 public:
    const int TICK_LENGTH = 1000;
    const int MILLISECONDS = 60000;
    std::function<void ()> callback;

    Timer(std::function<void ()> callback);
    void start();
    void stop();
    void tick();
};

#endif  // INCLUDE_TIMER_H_
