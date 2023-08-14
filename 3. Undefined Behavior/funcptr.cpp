#include <iostream>

static void (*funcptr)();

void evil() {
    std::cout << "All your bits are belong to us.\n";
}

void doomsday() {
    funcptr = evil;
}

int main() {
    std::cout << funcptr << "\n";
    funcptr();
}