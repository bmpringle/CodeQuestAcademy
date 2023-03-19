#include <iostream>
#include <string>

int main() {
    int tests;
    std::string buffer;

    std::cin >> tests;

    std::getline(std::cin, buffer);

    for(int i = 0; i < tests; ++i) {
        int sum = 0;

        std::getline(std::cin, buffer, ' ');
        sum += std::stoi(buffer) * 2;

        std::getline(std::cin, buffer, ' ');
        sum += std::stoi(buffer) * 4;

        std::getline(std::cin, buffer);
        sum += std::stoi(buffer) * 4;

        std::cout << sum << std::endl;
    }
    return 0;
}