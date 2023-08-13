#pragma once

#include <chrono>

// Timeout in absolute
class Timeout {
    std::chrono::steady_clock::time_point _timeout;

public:
    Timeout(std::chrono::steady_clock::duration duration)
    : _timeout(std::chrono::steady_clock::now() + duration)
    {}
};