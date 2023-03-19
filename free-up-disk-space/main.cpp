#include <iostream>
#include <ctime>
#include <set>
#include <math.h>
#include <iomanip>
#include <sstream>

typedef u_int64_t uint64;

struct DiskFile {
    std::string file_name;
    double score;
    double size;

    DiskFile(std::string name, double _score, double _size) : file_name(name), score(_score), size(_size) {

    }

    bool operator>(DiskFile rhs) const {
        if(score != rhs.score) {
            return score > rhs.score;
        }else if(file_name != rhs.file_name) {
            if(file_name.size() != rhs.file_name.size()) {
                return (file_name.size() > rhs.file_name.size()) ? true : false;
            }

            for(int i = 0; i < file_name.size(); ++i) {
                if(file_name[i] != rhs.file_name[i]) {
                    return file_name[i] > rhs.file_name[i];
                }
            }
        }else if(size != rhs.size) {
            return size > rhs.size;
        }

        abort(); //only possible through identical scores, file names, and sizes. this should never happen.
    }
};

std::tm today_tm = std::tm{0, 0, 0, 27, 4 - 1, 2019 - 1900};
std::time_t today = std::mktime(&today_tm); //get "today"'s time

void parseFile(std::string file_info, std::set<DiskFile, std::greater<DiskFile>>& files) {
    std::stringstream ss (file_info);
    std::string buffer = "";

    double age = 0;
    short day = -1;
    short month = -1;
    short year = -1;
    bool hasParsedTime = false;
    bool hasParsedAMPM = false;
    double fileSizeMB = -1;
    std::string file_name;

    while(std::getline(ss, buffer, ' ')) {
        if(day == -1 || month == -1 || year == -1) {
            std::string date_buffer = "";

            for(int i = 0; i < buffer.size(); ++i) {
                const char& c = buffer[i];

                if(c != '/') {
                    date_buffer += c;
                }

                if(c == '/' || i + 1 == buffer.size()) {
                    if(day == -1) {
                        day = std::stoi(date_buffer);
                        date_buffer.clear();
                        continue;
                    }

                    if(month == -1) {
                        month = std::stoi(date_buffer);
                        date_buffer.clear();
                        continue;
                    }

                    if(year == -1) {
                        year = std::stoi(date_buffer);
                        date_buffer.clear();
                        continue;
                    }
                }
            }
            continue;
        }

        if(!hasParsedTime) {
            hasParsedTime = true;
            continue;
        }

        if(!hasParsedAMPM) {
            if(buffer == "PM") {
                age -= 0.5;
            }

            hasParsedAMPM = true;

            continue;
        }

        if(fileSizeMB == -1) {
            fileSizeMB = std::stoi(buffer) / 1000.0;
            continue;
        }

        file_name = buffer;
        break;
    }

    std::tm before = std::tm{0, 0, 0, day, month - 1, year - 1900}; //get date of file

    age += std::difftime(today, std::mktime(&before)) / (60.0 * 60.0 * 24.0); //get age of file

    double score = age * fileSizeMB;

    score *= 1000.0;
    score = round(score);
    score /= 1000.0;

    files.insert({file_name, score, fileSizeMB}); //add to set
}

int main() {
    uint64 tests;
    std::string buffer;

    std::cin >> tests;

    std::getline(std::cin, buffer);

    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(3); //print 3 decimal places

    for(uint64 i = 0; i < tests; ++i) {
        uint64 fileCount;
        double hardDriveSize; // in GB

        std::cin >> fileCount;
        std::cin >> hardDriveSize;

        std::getline(std::cin, buffer);

        std::set<DiskFile, std::greater<DiskFile>> files;

        for(uint64 j = 0; j < fileCount; ++j) {
            std::getline(std::cin, buffer);

            parseFile(buffer, files);
        }

        double total = 0;
        for(const DiskFile& file : files) {
            total += file.size;

            std::cout << file.file_name << " " << file.score << std::endl;

            if(total >= hardDriveSize * 250.0) { //250.0 is 25% of 1000x, since it needs to be 1/4 of the MB
                break;
            }
        }
    }

    return 0;
}