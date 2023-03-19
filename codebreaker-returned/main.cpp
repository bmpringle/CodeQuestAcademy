#include <iostream>
#include <map>
#include <math.h>
#include <iomanip>
#include <algorithm>

int main() {
    int tests;
    std::string buffer;

    std::cin >> tests;
    std::getline(std::cin, buffer);

    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(3); //print 3 decimal places

    int lines;
    std::map<std::string, int> charFrequencyMapDigraph;
    std::map<std::string, int> charFrequencyMapTrigraph;

    for(int i = 0; i < tests; ++i) {
        lines = 0;
        charFrequencyMapDigraph.clear();
        charFrequencyMapTrigraph.clear();

        int totalDigraphs = 0;
        int totalTrigraphs = 0;

        std::string trigraphBuffer = "";
        std::string digraphBuffer = "";
        
        std::cin >> lines;
        std::getline(std::cin, buffer);

        for(int j = 0; j < lines; ++j) {
            trigraphBuffer = "";
            digraphBuffer = "";
            
            std::getline(std::cin, buffer);

            buffer.erase(std::remove_if(buffer.begin(), buffer.end(), [](const char& c) {
                if(isalpha(c) || c == ' ') {
                    return false;
                }
                return true;
            }), buffer.end());

            for(const char& c : buffer) { 
                if(isalpha(c)) {
                    digraphBuffer += toupper(c);
                    trigraphBuffer += toupper(c);

                    if(digraphBuffer.size() == 2) {
                        ++charFrequencyMapDigraph[digraphBuffer];
                        ++totalDigraphs;
                        digraphBuffer.erase(digraphBuffer.begin(), digraphBuffer.begin() + 1);
                    }

                    if(trigraphBuffer.size() == 3) {
                        ++charFrequencyMapTrigraph[trigraphBuffer];
                        ++totalTrigraphs;
                        trigraphBuffer.erase(trigraphBuffer.begin(), trigraphBuffer.begin() + 1);
                    }

                    continue;
                }

                trigraphBuffer = "";
                digraphBuffer = "";
            }
        }

        for(auto [letter, frequency] : charFrequencyMapDigraph) {
            double letter_frequency_percent = ((double)frequency / (double)totalDigraphs) * 100.0;

            letter_frequency_percent *= 1000.0;
            letter_frequency_percent = round(letter_frequency_percent);
            letter_frequency_percent /= 1000.0;

            std::cout << letter << ": " << letter_frequency_percent << "%" << std::endl;
        }

        for(auto [letter, frequency] : charFrequencyMapTrigraph) {
            double letter_frequency_percent = ((double)frequency / (double)totalTrigraphs) * 100.0;

            letter_frequency_percent *= 1000.0;
            letter_frequency_percent = round(letter_frequency_percent);
            letter_frequency_percent /= 1000.0;

            std::cout << letter << ": " << letter_frequency_percent << "%" << std::endl;
        }
    }
}