#include <iostream>

#define SQUARE(v) ((v)*(v))

int main() {
    int a = 3;

    std::cout << SQUARE(++a) << "\n";
    std::cout << ((++a)*(++a)) << "\n";
}