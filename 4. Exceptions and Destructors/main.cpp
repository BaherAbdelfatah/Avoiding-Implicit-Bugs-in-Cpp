#include "fd.h"
#include <fcntl.h>
#include <string.h>

void print(const FD& fd, const char *str)
{
    fd.write(str, strlen(str));
}

FD create_file(const char* file_name) {
    return FD{open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0666)};
}

int main()
{
    try {
        FD fd{};
        fd = create_file("somefile");
        print(fd, "Hello World\n");
        close(fd.get());
        print(fd, "How're the wife and kids?\n");
    } catch (std::exception& ex) {
        std::cerr << "Exception caught: " << ex.what() << "\n";
    }
    return 0;
}