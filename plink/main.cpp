#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
    int tests;
    std::string buffer;
    std::cin >> tests;

    std::getline(std::cin, buffer);

    for(int i = 0; i < tests; ++i) {
        int rows;
        std::cin >> rows;

        std::vector<std::vector<std::pair<int, std::string>>> tree;

        std::getline(std::cin, buffer);

        for(int j = 0; j < rows + 1; ++j) {
            tree.push_back({});
            std::getline(std::cin, buffer);
            buffer += " ";

            std::stringstream ss (buffer);

            int treeColumnIndex = 0;
            while(std::getline(ss, buffer, ' ')) {
                tree[j].push_back(std::pair<int, std::string>(std::stoi(buffer), std::string()));
                ++treeColumnIndex;
            }
        }

        if(tree.size() == 2) {
            if(tree[1][0] > tree[1][1]) {
                std::cout << "L" << " = " << (tree[0][0].first + tree[1][0].first) << std::endl;
            }else {
                std::cout << "R" << " = " << (tree[0][0].first + tree[1][1].first) << std::endl;
            }
            continue;
        }

        for(int j = tree.size() - 2; j >= 0; --j) {
            for(int k = 0; k < tree[j].size(); ++k) {
                if(tree[j + 1][k] > tree[j + 1][k + 1]) {
                    tree[j][k].first += tree[j + 1][k].first;
                    tree[j][k].second += tree[j + 1][k].second + "L";
                }else {
                    tree[j][k].first += tree[j + 1][k + 1].first;
                    tree[j][k].second += tree[j + 1][ + 1].second + "R";
                }
            }
        }

        std::reverse(tree[0][0].second.begin(), tree[0][0].second.end());

        std::cout << tree[0][0].second << " = " << tree[0][0].first << std::endl;
    }

    return 0;
}