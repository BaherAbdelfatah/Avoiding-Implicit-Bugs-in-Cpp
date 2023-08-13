#include "fd.h"
#include <fcntl.h>
#include <string.h>

void print(const FD& fd, const char *str)
{
    //std::cerr << "Main " << __PRETTY_FUNCTION__ << ": fd=" << fd.get() << " this=" << &fd << "\n";
    fd.write(str, strlen(str));
}

FD create_file(const char* file_name) {
    return FD{open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0666)};
}

int main()
{
    FD fd{};
    fd = create_file("somefile");
    //std::cerr << "Main " << __PRETTY_FUNCTION__ << ": fd=" << fd.get() << " this=" << &fd << "\n";
    print(fd, "Hello World\n");
    //std::cerr << "Main " << __PRETTY_FUNCTION__ << ": fd=" << fd.get() << " this=" << &fd << "\n";
    print(fd, "How're the wife and kids?\n");
    //std::cerr << "Main " << __PRETTY_FUNCTION__ << ": fd=" << fd.get() << " this=" << &fd << "\n";
    return 0;
}