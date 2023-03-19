#include <iostream>

int main() {
    int tests;
    std::cin >> tests;

    for(int i = 0; i < tests; ++i) {
        std::string buffer = "";

        double V, X;
        std::getline(std::cin, buffer, ':');
        V = std::stod(buffer);

        std::getline(std::cin, buffer, '\n');
        X = std::stod(buffer);

        if(X - V <= 0) {
            std::cout << "SWERVE" << std::endl;
        }else if(X - 5*V <= 0) {
            std::cout << "BRAKE" << std::endl;
        }else {
            std::cout << "SAFE" << std::endl;
        }
    }

    return 0;
}