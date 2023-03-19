#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

int doOppositeOperation(const int& left, const char& operation, const int& right) {
    if(operation == '+') {
        return left - right;
    }else if(operation == '-') {
        return left + right;
    }else if(operation == '*') {
        return left / right;
    }else if(operation == '/') {
        return left * right;
    }

    return INFINITY;
}

bool isOperandOperatorTargetValid(int target, std::vector<int> operands, std::unordered_map<char, int> operators, int depth = 0) {
    if(operators.size() == 0) {
        if(target == operands.at(0)) {
            return true;
        }else {
            return false;
        }
    }
    
    for(int i = 0; i < operands.size(); ++i) {
        for(auto [operator_, count] : operators) {
            if(count > 0) {
                int operand = operands[i];
                operands.erase(operands.begin() + i);
                --count;
                if(isOperandOperatorTargetValid(doOppositeOperation(target, operator_, operand), operands, operators, depth + 1)) {
                    return true;
                }
                ++count;
                operands.push_back(operand);
            }
        }
    }

    return false;
}

int main() {
    int tests;
    std::string buffer;
    std::string buffer2;

    int target;
    std::vector<int> operands;
    std::unordered_map<char, int> operators;

    std::cin >> tests;
    std::getline(std::cin, buffer);

    for(int i = 0; i < tests; ++i) {
        std::getline(std::cin, buffer, ':');
        target = std::stoi(buffer);

        std::getline(std::cin, buffer, '\n');

        for(const char& c : buffer) {
            if(c == ' ') {
                if(buffer2 == "+") {
                    ++operators['+'];
                }else if(buffer2 == "-") {
                    ++operators['-'];
                }else if(buffer2 == "*") {
                    ++operators['*'];
                }else if(buffer2 == "/") {
                    ++operators['/'];
                }else {
                    operands.push_back(std::stoi(buffer2));
                }

                buffer2 = "";

            }else {
                buffer2 += c;
            }
        }


        if(isOperandOperatorTargetValid(target, operands, operators)) {
            std::cout << "TRUE" << std::endl;
        }else {
            std::cout << "FALSE" << std::endl;
        }

    }

    return 0;
}