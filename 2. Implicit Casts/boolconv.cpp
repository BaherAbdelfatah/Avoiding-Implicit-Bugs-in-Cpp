#include <iostream>

class C {
public:
    explicit operator bool() const {
        return true;
    }
};

void foo(int i) {
    std::cout << i << "\n";
}

int main() {
    C c;

    if (c) {
        std::cout << "true\n";
    }

    // foo(c);
}