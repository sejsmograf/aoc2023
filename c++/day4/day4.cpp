#include <iostream>
#include <sstream>
#include <vector>

int main() {
    std::string line;
    bool winning[100] = {false};
    int sum = 0;
    std::vector<int> winningCards;

    std::string word;

    while (std::getline(std::cin, line)) {
        int win = 0;
        std::stringstream ss(line);

        ss.ignore(line.length(), ':');

        while (ss >> word && word != "|") {
            winning[stoi(word)] = true;
        }

        while (ss >> word) {
            if (winning[stoi(word)]) {
                if (win != 0) {
                    win = win << 1;
                } else {
                    win = 1;
                }
            }
        }
        sum += win;

        std::fill(std::begin(winning), std::end(winning), false);
    }

    std::cout << sum;
}