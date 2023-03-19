#include <iostream>

int main() {
    int tests;
    std::string buffer;

    std::cin >> tests;

    std::getline(std::cin, buffer, '\n');

    for(int i = 0; i < tests; ++i) {
        std::string hex;
        std::string type;

        std::getline(std::cin, hex, ' ');
        std::getline(std::cin, type, '\n');
        
        if(type == "LITTLE") {
            std::string big_endian_string = "";

            for(int i = hex.size() - 1; i >= 0; --i) {
                if(i % 2 == 0) {
                    big_endian_string += hex[i];
                    big_endian_string += hex[i + 1];
                }
            }

            hex = big_endian_string;
        }

        std::cout << std::stol(hex, 0, 16) << std::endl;
    }

    return 0;
}