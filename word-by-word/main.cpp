#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <string>
#include <cmath>
#include <limits.h>

void processAndGenerateOutput(std::map<int, int>& wordLengthFrequencies, const int totalWordCount, const int smallest, const int largest) {
    //declare variables

    double average = 0;
    std::vector<int> modes;
    int currentModesCount = 0;

    int medianCountForwards = 0;
    int medianCountBackwards = 0;
    int medianCountWordLengthKey = -1;
    int lengthStradleKey = -1;
    bool stradlesLengths = false;
    const int range = largest - smallest;

    //loop over map of wod lengths --> number of words in sample data with that word length map
    for(auto [wordLength, wordCount] : wordLengthFrequencies) {
        //sets lengthStradleKey if stradlesLengths is set to true. this will be explained where stradlesLengths is set
        if(lengthStradleKey == -1 && stradlesLengths) { 
            lengthStradleKey = wordLength;
        }

        //calculate running sum in order to find average word length
        average += wordLength * wordCount;

        //if current word length has the same number of words as current mode, add to the mode list
        if(wordCount == currentModesCount) { 
            modes.push_back(wordLength);
        
        //if current word length has more words than the current mode, reset mode list and add it
        }else if(wordCount > currentModesCount) {
            modes.clear();
            modes.push_back(wordLength);

            currentModesCount = wordCount;
        }

        //keeps a running tally of the number of words that have been processed in this loop, and on the
        //word length that processes half of them, we know that must be the median.
        if(medianCountForwards < totalWordCount / 2.0 && medianCountForwards + wordCount >= totalWordCount / 2.0) {
            medianCountWordLengthKey = wordLength;

            //if the current word length processed exactly half of the words, then the median is actually
            //the average of the current and next word lengths. therefore, set stradlesLengths so we can
            //store the next word length as well in the next for loop iteration.
            if(medianCountForwards + wordCount == totalWordCount / 2.0) {
                stradlesLengths = true;
            }
        }

        medianCountForwards += wordCount;
    }

    double median = 0.0;

    //calculate median based on the results of the for loop
    if(!stradlesLengths) {
        median = medianCountWordLengthKey;
    }else {
        median = (medianCountWordLengthKey + lengthStradleKey) / 2.0;
    }

    //divide running sum to find average
    average /= (double) totalWordCount;

    //round average and median to the nearest 10th
    average *= 10.0;
    median *= 10.0;

    average = round(average);
    median = round(median);

    average /= 10.0;
    median /= 10.0;

    //format average to always have a .0 on the end, even if average is an integer
    if(trunc(average) != average) {
        std::cout << "Average: " << average << std::endl;
    }else {
        std::cout << "Average: " << average << ".0" << std::endl;
    }

    //format median to always have a .0 on the end, even if median is an integer
    if(trunc(median) != median) {
        std::cout << "Median: " << median << std::endl;
    }else {
        std::cout << "Median: " << median << ".0" << std::endl;
    }
    
    //print out the modes
    std::cout << "Modes: ";

    for(int i = 0; i < modes.size(); ++i) {
        std::cout << modes[i];
        
        if(i + 1 < modes.size()) {
            std::cout << ",";
        }
    }

    std::cout << std::endl;

    //print out the range
    std::cout << "Range: " << range << std::endl;

    //print out the graph
    for(int i = smallest; i <= largest; ++i) {

        if(i < 10) {
            std::cout << " ";
        }

        std::cout << i << "|";

        for(int _ = 0; _ < wordLengthFrequencies[i]; ++_) {
            std::cout << "x";
        }

        std::cout << std::endl;
    }
}

void handleEndOfWord(std::map<int, int>& wordLengthMap, int& wordCount, int& shortest, int& longest, int& wordLength) {
    if(wordLength == 0) {
        return;
    }

    //not a letter and there were letters previously since wordLength > 0, so we've reached the end of a word
    ++wordLengthMap[wordLength];

    ++wordCount;

    //find the shortest and longest words, useful later for finding the range and creating the graph
    if(wordLength < shortest) {
        shortest = wordLength;
    }

    if(wordLength > longest) {
        longest = wordLength;
    }

    //reset wordLength variable so it can be reused for next word
    wordLength = 0;
}

bool isCharALetter(const char& c) {
    //Uses ASCII values for the letters 'a', 'z', 'A', and 'Z'
    return (c >= (int)'a' && c <= (int)'z') || (c >= (int)'A' && c <= (int)'Z'); 
}

int main() {
    int tests;
    std::string buffer;

    std::cin >> tests; //get number of test cases
    std::getline(std::cin, buffer); //flush std::cin

    //run through each test case
    for(int i = 0; i < tests; ++i) {
        int lines;
        std::map<int, int> wordLengthFrequencyMap;
        int shortestWordLength = INT_MAX;
        int longestWordLength = 0;
        int totalWordCount = 0;

        //get the number of lines in each test case
        std::cin >> lines;
        std::getline(std::cin, buffer); //flush std::cin

        int wordLength = 0;

        for(int j = 0; j < lines; ++j) {
            std::getline(std::cin, buffer, '\n'); //grab a line of text

            for(int k = 0; k < buffer.size(); ++k) {
                const char& c = buffer[k];

                if(k > 0 && k + 1 < buffer.size() && c == '\'') {
                    if(isCharALetter(buffer[k - 1]) && isCharALetter(buffer[k + 1])) {
                        //if all conditions are met, the apostrophe is a contractions and therefore should not be counted.
                        continue;
                    }
                }

                //check if character c is a letter or some other symbol
                if(!isCharALetter(c)) {
                    handleEndOfWord(wordLengthFrequencyMap, totalWordCount, shortestWordLength, longestWordLength, wordLength);

                    continue; 
                }

                ++wordLength;
            }

            handleEndOfWord(wordLengthFrequencyMap, totalWordCount, shortestWordLength, longestWordLength, wordLength);
        }

        if(totalWordCount == 0) {
            shortestWordLength = 0;
        }

        //process map and generate output
        processAndGenerateOutput(wordLengthFrequencyMap, totalWordCount, shortestWordLength, longestWordLength);
    }

    return 0;
}