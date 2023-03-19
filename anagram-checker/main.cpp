#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<char, int> wordOne;
    std::unordered_map<char, int> wordTwo;
    int test;
    std::string inputBuffer;
    std::string wordOneStore;
    std::string wordTwoStore;

    std::cin >> test;

    std::getline(std::cin, inputBuffer);

    for(int i = 0; i < test; ++i) {
        wordOneStore = "";
        wordTwoStore = "";
        inputBuffer = "";
        wordOne.clear();
        wordTwo.clear();

        std::getline(std::cin, inputBuffer, '|');

        wordOneStore = inputBuffer;

        for(const char& c : inputBuffer) {
            ++wordOne[c];
        }

        std::getline(std::cin, inputBuffer);

        wordTwoStore = inputBuffer;

        for(const char& c : inputBuffer) {
            ++wordTwo[c];
        }

        if(wordOne.size() != wordTwo.size() || wordOneStore == wordTwoStore) {
            std::cout << wordOneStore + std::string("|") + wordTwoStore << " = NOT AN ANAGRAM" << std::endl;
            continue;
        }

        bool failed = false;

        for(auto [c, count] : wordOne) {
            if(count != wordTwo[c]) {
                failed = true;
                break;
                std::cout << wordOneStore + std::string("|") + wordTwoStore << " = NOT AN ANAGRAM" << std::endl;
            }
        }

        if(!failed) {
            std::cout << wordOneStore + std::string("|") + wordTwoStore << " = ANAGRAM" << std::endl;
        }else {
            std::cout << wordOneStore + std::string("|") + wordTwoStore << " = NOT AN ANAGRAM" << std::endl;
        }
    }

    return 0;
}