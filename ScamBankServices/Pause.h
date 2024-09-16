// Console pause file

#ifndef PAUSE_H
#define PAUSE_H

#include <chrono>
#include <thread>

// Pause console for certain seconds
void pause(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

#endif