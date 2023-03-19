#include <iostream>
#include <math.h>

void calculateTerms(std::string input_number) {
    std::string first_term = "";
    std::string decimal = "";
    bool parsing_first_term = true;

    for(const char& c : input_number) {
        if(!parsing_first_term) {
            decimal += c;
            continue;
        }

        if(c != '.') {
            first_term += c;
        }

        if(c == '.') {
            parsing_first_term = false;
        }
    }

    std::cout << first_term;

    if(decimal == "") {
        std::cout << std::endl;
        return;
    }

    long long fraction_numerator = std::stoll(decimal);
    long long fraction_denominator = pow(10, decimal.size());

    for(int i = 1; i < 10; ++i) { //do nine more terms
        std::cout << " " << (fraction_denominator / fraction_numerator);

        long long remainder = fraction_denominator % fraction_numerator;

        fraction_denominator = fraction_numerator;
        fraction_numerator = remainder;

        if(remainder == 0) {
            break;
        }
    }

    std::cout << std::endl;
}

int main() {
    int tests;
    std::cin >> tests;

    std::string buffer;
    std::getline(std::cin, buffer);

    for(int i = 0; i < tests; ++i) {
        std::getline(std::cin, buffer);

        calculateTerms(buffer);
    }
}