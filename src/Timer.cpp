//  Copyright 2022
#include "../include/Timer.h"

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <functional>

Timer::Timer(std::function<void ()> callback) {
    this->callback = callback;
}

void Timer::start() {
    t = new std::thread([this](){tick();});
}

void Timer::stop() {
    shouldStop = true;
    t->join();
}

void Timer::tick()
{
    while (!shouldStop) {
        std::this_thread::sleep_for(std::chrono::milliseconds(TICK_LENGTH));
        callback();
    }
}

