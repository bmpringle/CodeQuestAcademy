#include <iostream>
#include <string>

int main() {
    int tests;
    std::cin >> tests;

    std::string buffer;
    std::getline(std::cin, buffer, '\n'); //get rid of the newline in std::cin

    for(int i = 0; i < tests; ++i) {
        std::getline(std::cin, buffer, '\n');

        int vowels = 0;

        for(const char& c : buffer) {
            switch(c) {
                case 'a':
                    ++vowels;
                    break;
                case 'e':
                    ++vowels;
                    break;
                case 'i':
                    ++vowels;
                    break;
                case 'o':
                    ++vowels;
                    break;
                case 'u':
                    ++vowels;
                    break;
                default:
                    break;
            }
        }

        std::cout << vowels << std::endl;
    }

    return 0;
}