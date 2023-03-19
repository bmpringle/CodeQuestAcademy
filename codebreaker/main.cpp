#include <iostream>
#include <map>
#include <math.h>
#include <iomanip>

int main() {
    int tests;
    std::string buffer;

    std::cin >> tests;
    std::getline(std::cin, buffer);

    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2); //print 2 decimal places

    int lines;
    std::map<char, int> charFrequencyMap;

    for(int i = 0; i < tests; ++i) {
        lines = 0;
        
        for(int j = (int)'A'; j <= (int)'Z'; ++j) {
            charFrequencyMap[j] = 0;
        }

        int totalLetters = 0;
        
        std::cin >> lines;
        std::getline(std::cin, buffer);

        for(int j = 0; j < lines; ++j) {
            std::getline(std::cin, buffer);

            for(const char& c : buffer) { 
                if(isalpha(c)) {
                    ++charFrequencyMap[toupper(c)];
                    ++totalLetters;
                }
            }
        }

        for(auto [letter, frequency] : charFrequencyMap) {
            double letter_frequency_percent = ((double)frequency / (double)totalLetters) * 100.0;

            letter_frequency_percent *= 100.0;
            letter_frequency_percent = round(letter_frequency_percent);
            letter_frequency_percent /= 100.0;

            std::cout << letter << ": " << letter_frequency_percent << "%" << std::endl;
        }
    }
}