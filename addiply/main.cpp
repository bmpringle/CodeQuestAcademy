#include <iostream>

int main() {
    int tests;
    std::cin >> tests;

    for(int i = 0; i < tests; ++i) {
        int x, y;
        std::cin >> x;
        std::cin >> y;

        std::cout << x + y << " " << x * y << std::endl;
    }
    
    return 0;
}