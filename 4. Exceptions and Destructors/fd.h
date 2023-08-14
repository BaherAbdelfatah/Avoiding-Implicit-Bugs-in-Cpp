#pragma once

#include <system_error>
#include <unistd.h>

#include <iostream>
#include <utility>

class FD
{
    int _fd;

public:
    explicit FD() : _fd(-1) {}
    explicit FD(int fd) : _fd(fd)
    {
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

    FD& operator=(FD other) {
        swap(*this, other);

        return *this;
    }

    ~FD() noexcept
    {
        try {
            close();
        } catch (std::exception& ex) {
        std::cerr << "Destructor caught exception: " << ex.what() << "\n";
    }
    }

    void close()
    {
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