#include <iostream>
#include <string>
#include <array>

struct Block {
    long timestamp = 0;
    int value = 0;
    int index = 0;
    double previousHash = 0;
};

double lmcoinHash(Block& blockToHash) {
    return ((double)(blockToHash.previousHash + blockToHash.timestamp + blockToHash.value + blockToHash.index) * 50.0 / 147.0);
}

int main() {
    std::string buffer;
    int tests;
    std::cin >> tests;

    std::getline(std::cin, buffer);

    for(int i = 0; i < tests; ++i) {
        std::array<Block, 10> blockchain;
        std::array<int, 10> data;
        std::array<long, 10> timestamps;

        for(int j = 0; j < 9; ++j) {
            std::getline(std::cin, buffer, ' ');

            int value = 0;

            for(int k = 0; k < buffer.size(); ++k) {
                value += (int)buffer[k] - (int)'a' + 1;
            }

            data[j] = value;
        }
        
        std::getline(std::cin, buffer, '\n');

        int value = 0;

        for(int k = 0; k < buffer.size(); ++k) {
            value += (int)buffer[k] - (int)'a' + 1;
        }

        data[9] = value;

        for(int j = 0; j < 9; ++j) {
            std::getline(std::cin, buffer, ' ');

            timestamps[j] = std::stol(buffer); 
        }

        std::getline(std::cin, buffer, '\n');

        timestamps[9] = std::stol(buffer); 

        double prevHash = 0;

        for(int j = 0; j < 10; ++j) {
            Block block = Block();
            block.index = j + 1;
            block.previousHash = prevHash;
            block.value = data[j];
            block.timestamp = timestamps[j];
            
            prevHash = lmcoinHash(block);

            blockchain[j] = block;
        }

        std::cout << (long)(lmcoinHash(blockchain[9]) + 0.5) << std::endl;
    }
    return 0;
}