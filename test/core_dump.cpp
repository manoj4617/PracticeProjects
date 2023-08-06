#include <iostream>

int main() {
    char* str = nullptr;
    *str = 'a'; // This will cause a segmentation fault
    return 0;
}
