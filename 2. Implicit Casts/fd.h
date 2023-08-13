#pragma once

#include "nocopy.h"

#include <system_error>
#include <unistd.h>

#include <iostream>
#include <utility>

class FD : private NoCopy
{
    int _fd;

public:
    FD() : _fd(-1) {}
    explicit FD(int fd) : _fd(fd)
    {
        // std::cerr << "FD " << __PRETTY_FUNCTION__ << ": fd=" << _fd << " this=" << this << "\n";
        if (-1 == fd)
        {
            throw std::system_error{std::error_code(errno, std::system_category())};
        }
    }

    FD(const FD& other) : _fd(-1) {
        if (other) {
            _fd = dup(other.get());
            if (-1 == _fd) {
                throw std::system_error{std::error_code(errno, std::system_category())};
            }
        }
    }

    // FD(FD&& other) : _fd(other._fd) {
    //     other._fd = -1;
    // }

    // FD& operator=(const FD& other) {
    FD& operator=(FD other) {
        // FD temp(other);
        swap(*this, other);
        // if (&other != this) {
        //     close();
        //     if (other) {
        //         _fd = dup(other.get());
        //         if (1 == _fd) {
        //             throw std::system_error{std::error_code(errno, std::system_category())};
        //         }
        //     }
        // }

        return *this;
    }

    // FD& operator=(FD&& other) {
    //     FD temp(std::move(other));
    //     swap(*this, temp);
    //     // close();
    //     // _fd = other._fd;
    //     // other._fd = -1;
    //     return *this;
    // }

    ~FD()
    {
        // std::cerr << "FD " << __PRETTY_FUNCTION__ << ": fd=" << _fd << " this=" << this << "\n";
        close();
    }

    void close()
    {
        // std::cerr << "FD " << __PRETTY_FUNCTION__ << ": fd=" << _fd << " this=" << this << "\n";
        if (_fd != -1)
        {
            if (-1 == ::close(_fd))
            {
                throw std::system_error{std::error_code(errno, std::system_category())};
            }
            _fd = -1;
        }
    }

    int get() const
    {
        return _fd;
    }

    explicit operator bool() const
    { // if(fd) {}
        return _fd != -1;
    }

    ssize_t write(const void *buf, size_t count) const
    {
        // std::cerr << "FD " << __PRETTY_FUNCTION__ << ": fd=" << _fd << " this=" << this << "\n";
        ssize_t result = ::write(_fd, buf, count);
        if (-1 == result)
        {
            throw std::system_error{std::error_code(errno, std::system_category())};
        }
        return result;
    }

    friend void swap(FD &a, FD & b) noexcept {
        std::swap(a._fd, b._fd);
    }
};