#include <iostream>
#include <vector>
#include <math.h>

struct LaunchInfo {
    LaunchInfo(int _x, int _y, double _time) : x(_x), y(_y), time(_time) {

    }

    int x;
    int y;
    double time;
};

std::string formatBurntime(double burn_time) {
    burn_time *= 100.0;

    burn_time = round(burn_time);

    burn_time /= 100.0;

    std::string formatted_string = std::to_string(burn_time);

    if(formatted_string.find('.') == std::string::npos) {
        formatted_string += ".";
    }

    while(formatted_string.substr(formatted_string.find('.')).size() - 1 < 2) {
        formatted_string += "0";
    }

    while(formatted_string.substr(formatted_string.find('.')).size() - 1 > 2) {
        formatted_string.pop_back();
    }

    return formatted_string;
}

double determineBurnTime(int displacement, double time) {
    if(time * time - 4 * displacement < 0) {
        abort();
    }

    double v1 = time + sqrt(time * time - 4 * displacement);
    double v2 = time - sqrt(time * time - 4 * displacement);

    return std::min(abs(v1), abs(v2));
}

int main() {
    int tests;
    std::cin >> tests;

    for(int i = 0; i < tests; ++i) {
        int S, x, y;
        std::string buffer;

        std::cin >> S;
        std::cin >> x;
        std::cin >> y;
        
        std::getline(std::cin, buffer);

        std::vector<LaunchInfo> launchInformation;

        for(int j = 0; j < S; ++j) {
            int x_cube_sat, y_cube_sat;
            double time;
            std::cin >> x_cube_sat;
            std::cin >> y_cube_sat;
            std::cin >> time;

            launchInformation.push_back(LaunchInfo(x_cube_sat, y_cube_sat, time));

            std::getline(std::cin, buffer);
        }

        double burn_time = 0;

        for(const LaunchInfo& info : launchInformation) {
            int displacement_x = abs(info.x - x);
            int displacement_y = abs(info.y - y);

            burn_time += determineBurnTime(displacement_x, info.time);
            burn_time += determineBurnTime(displacement_y, info.time);

            x = info.x;
            y = info.y;
        }

        std::cout << formatBurntime(burn_time) << std::endl;
    }

    return 0;
}