#include <iostream>
#include <sstream>
#include <string>

#include "AocProblem.h"

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14
#define RED "red"
#define GREEN "green"
#define BLUE "blue"

int main() {
    std::string line;
    int sumPartOne = 0;
    int sumPartTwo = 0;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string word;
        ss >> word;  // Skip "Game" word
        ss >> word;  // Get the game number
        int gameNumber = stoi(word);

        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;

        bool valid = true;
        while (ss >> word) {
            int dicesNumber = stoi(word);
            ss >> word;
            std::string diceColor;
            if (word[word.length() - 1] == ',' ||
                word[word.length() - 1] == ';') {
                diceColor = word.substr(0, word.length() - 1);
            } else {
                diceColor = word;
            }

            if (diceColor == RED && dicesNumber > maxRed) {
                maxRed = dicesNumber;
            }
            if (diceColor == GREEN && dicesNumber > maxGreen) {
                maxGreen = dicesNumber;
            }
            if (diceColor == BLUE && dicesNumber > maxBlue) {
                maxBlue = dicesNumber;
            }

            if (diceColor == RED && dicesNumber > MAX_RED) {
                valid = false;
            }
            if (diceColor == GREEN && dicesNumber > MAX_GREEN) {
                valid = false;
            }
            if (diceColor == BLUE && dicesNumber > MAX_BLUE) {
                valid = false;
            }
        }

        int power = maxGreen * maxRed * maxBlue;
        sumPartTwo += power;

        if (valid) {
            sumPartOne += gameNumber;
        }
    }
    std::cout << sumPartOne << "\n";
    std::cout << sumPartTwo << "\n";
}