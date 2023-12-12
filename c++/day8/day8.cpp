#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../AocProblem.h"

class Day8 : public AocProblem {
   public:
    void solvePartOne() override {
        calculateSilver();
        std::cout << "Part one: " << silver << "\n";
    }
    void solvePartTwo() override {
        calculateGold();
        std::cout << "Part two: " << gold << "\n";
    }

   private:
    unsigned long long silver;
    unsigned long long gold;
    bool silverSolved = false;
    bool goldSolved = false;

    void calculateSilver() {
        if (silverSolved) {
            return;
        }
        std::string line;
        std::unordered_map<std::string, std::pair<std::string, std::string>>
            map;

        std::getline(std::cin, line);
        std::string directions = line;

        std::getline(std::cin, line);

        while (std::getline(std::cin, line)) {
            std::string location, leftDestination, rightDestination;
            std::stringstream ss(line);
            ss >> location;
            ss.ignore(line.length(), '(');
            ss >> leftDestination;
            ss >> rightDestination;

            map[location] = std::make_pair(
                leftDestination.substr(0, leftDestination.length() - 1),
                rightDestination.substr(0, rightDestination.length() - 1));
        }

        int silverSolution = 0;
        bool breakWhile = false;
        std::string currentPosition = "AAA";
        while (!breakWhile) {
            for (char c : directions) {
                if (c == 'L') {
                    currentPosition = map[currentPosition].first;
                } else {
                    currentPosition = map[currentPosition].second;
                }
                silverSolution++;
                if (currentPosition == "ZZZ") {
                    breakWhile = true;
                    break;
                }
            }
        }
        silver = silverSolution;
        silverSolved = true;
    }

    void calculateGold() {
        if (goldSolved) {
            return;
        }
        std::string line;
        std::unordered_map<std::string, std::pair<std::string, std::string>>
            map;

        std::vector<std::string> startingLocations;
        std::getline(std::cin, line);
        std::string directions = line;

        std::getline(std::cin, line);

        while (std::getline(std::cin, line)) {
            std::string location, leftDestination, rightDestination;
            std::stringstream ss(line);
            ss >> location;
            ss.ignore(line.length(), '(');
            ss >> leftDestination;
            ss >> rightDestination;

            if (location[location.length() - 1] == 'A') {
                startingLocations.push_back(location);
            }
            map[location] = std::make_pair(
                leftDestination.substr(0, leftDestination.length() - 1),
                rightDestination.substr(0, rightDestination.length() - 1));
        }

        std::vector<int> stepsForLocations;
        for (const auto& loc : startingLocations) {
            int stepsForCurrentLocation = 0;
            bool breakWhile = false;
            std::string currentLocation = loc;
            while (!breakWhile) {
                for (char c : directions) {
                    if (c == 'L') {
                        currentLocation = map[currentLocation].first;
                    } else {
                        currentLocation = map[currentLocation].second;
                    }
                    stepsForCurrentLocation++;
                    if (currentLocation[currentLocation.length() - 1] == 'Z') {
                        breakWhile = true;
                        stepsForLocations.push_back(stepsForCurrentLocation);
                        break;
                    }
                }
            }
        }
        unsigned long long goldSolution = stepsForLocations[0];
        for (int i = 0; i < stepsForLocations.size(); i++) {
            goldSolution = std::lcm(goldSolution, stepsForLocations[i]);
        }

        gold = goldSolution;
        goldSolved = true;
    }
};

int main() {
    Day8 day;
    day.solvePartTwo();
    day.solvePartTwo();
}
