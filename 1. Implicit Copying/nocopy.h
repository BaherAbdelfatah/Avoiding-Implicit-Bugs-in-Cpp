#pragma once

class NoCopy {
public:
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;

    NoCopy(NoCopy&& that) = default;
    NoCopy& operator=(NoCopy&&) = default;
};