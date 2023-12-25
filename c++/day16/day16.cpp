#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../AocProblem.h"

class Day16 : public AocProblem {
   public:
    void solvePartOne() {
        solve();
        std::cout << "Part one: " << silver << "\n";
    }
    void solvePartTwo() {
        solve();
        std::cout << "Part two: " << gold << "\n";
    }

   private:
    int silver;
    int gold;
    bool silverSolved = false;
    bool goldSolved = false;

    void solve() {
        if (silverSolved || goldSolved) {
            return;
        }

        std::string line;
        std::vector<std::string> area;
        while (std::getline(std::cin, line)) {
            area.push_back(line);
        }

        std::vector<std::vector<int>> energizedArea(
            area.size(), std::vector<int>(area[0].size(), 0));

        int max = 0;
        for (int i = 0; i < area.size(); i++) {
            energizedArea = std::vector<std::vector<int>>(
                area.size(), std::vector<int>(area[0].size(), 0));
            bounceLight(area, energizedArea, {0,1}, {i, 0});
            int sum = 0;
            for (const auto sejsmo : energizedArea) {
                for (const auto mandzio : sejsmo) {
                    if (mandzio) {
                        sum++;
                    }
                }
            }
            if(sum > max){
                max = sum;
            }
        }
        for (int i = 0; i < area.size(); i++) {
            energizedArea = std::vector<std::vector<int>>(
                area.size(), std::vector<int>(area[0].size(), 0));
            bounceLight(area, energizedArea, {0,-1}, {i, area.size()});
            int sum = 0;
            for (const auto sejsmo : energizedArea) {
                for (const auto mandzio : sejsmo) {
                    if (mandzio) {
                        sum++;
                    }
                }
            }
            if(sum > max){
                max = sum;
            }
        }

        for (int i = 0; i < area[0].size(); i++) {
            energizedArea = std::vector<std::vector<int>>(
                area.size(), std::vector<int>(area[0].size(), 0));
            bounceLight(area, energizedArea, {1,0}, {0, i});
            int sum = 0;
            for (const auto sejsmo : energizedArea) {
                for (const auto mandzio : sejsmo) {
                    if (mandzio) {
                        sum++;
                    }
                }
            }
            if(sum > max){
                max = sum;
            }
        }
        for (int i = 0; i < area[0].size(); i++) {
            energizedArea = std::vector<std::vector<int>>(
                area.size(), std::vector<int>(area[0].size(), 0));
            bounceLight(area, energizedArea, {-1,0}, {area.size()-1, i});
            int sum = 0;
            for (const auto sejsmo : energizedArea) {
                for (const auto mandzio : sejsmo) {
                    if (mandzio) {
                        sum++;
                    }
                }
            }
            if(sum > max){
                max = sum;
            }
        }

        silver = max;
        std::cout<< "max found : " << max;
    }

    enum Direction {
        UP = 1 << 0,
        DOWN = 1 << 1,
        LEFT = 1 << 2,
        RIGHT = 1 << 3
    };

    int getDirectionValue(std::pair<int, int> direction) {
        if (direction.first == 1) {
            return UP;
        } else if (direction.first == -1) {
            return DOWN;
        } else if (direction.second == 1) {
            return LEFT;
        } else if (direction.second == -1) {
            return RIGHT;
        }
    }

    bool containsDirection(int value, std::pair<int, int> direction) {
        return (value & getDirectionValue(direction));
    }

    void bounceLight(const std::vector<std::string>& area,
                     std::vector<std::vector<int>>& energizedArea,
                     std::pair<int, int> direction = {0, 1},
                     std::pair<int, int> currentLightLocation = {0, 0}) {
        if (currentLightLocation.first >= 0 &&
            currentLightLocation.first < area.size() &&
            currentLightLocation.second >= 0 &&
            currentLightLocation.second < area[0].size()) {

            if (containsDirection(energizedArea[currentLightLocation.first]
                                               [currentLightLocation.second],
                                  direction)) {
                return;
            }
            energizedArea[currentLightLocation.first]
                         [currentLightLocation.second] +=
                getDirectionValue(direction);
            std::pair<int, int> nextDirection = getNextDirection(
                direction,
                area[currentLightLocation.first][currentLightLocation.second]);
            if (nextDirection.first == -2) {
                bounceLight(area, energizedArea, {-1, 0},
                            {currentLightLocation.first - 1,
                             currentLightLocation.second});
                bounceLight(area, energizedArea, {1, 0},
                            {currentLightLocation.first + 1,
                             currentLightLocation.second});
            } else if (nextDirection.second == -2) {
                bounceLight(area, energizedArea, {0, -1},
                            {currentLightLocation.first,
                             currentLightLocation.second - 1});
                bounceLight(area, energizedArea, {0, 1},
                            {currentLightLocation.first,
                             currentLightLocation.second + 1});
            } else {
                bounceLight(
                    area, energizedArea, nextDirection,
                    {currentLightLocation.first + nextDirection.first,
                     currentLightLocation.second + nextDirection.second});
            }
        }
    }

    std::pair<int, int> getNextDirection(std::pair<int, int> currentDirection,
                                         char mirror) {
        switch (mirror) {
            case '.':
                return currentDirection;
            case '|':
                if (currentDirection.second != 0) {
                    return {-2, 0};
                } else {
                    return currentDirection;
                }
            case '-':
                if (currentDirection.first != 0) {
                    return {0, -2};
                } else {
                    return currentDirection;
                }

            case '/':
                if (currentDirection.first == 1) {
                    return {0, -1};
                } else if (currentDirection.first == -1) {
                    return {0, 1};
                } else if (currentDirection.second == 1) {
                    return {-1, 0};
                } else if (currentDirection.second == -1) {
                    return {1, 0};
                }
            case '\\':
                if (currentDirection.first == 1) {
                    return {0, 1};
                } else if (currentDirection.first == -1) {
                    return {0, -1};
                } else if (currentDirection.second == 1) {
                    return {1, 0};
                } else if (currentDirection.second == -1) {
                    return {-1, 0};
                }
        }
        return currentDirection;
    }
};

int main() {
    Day16 day;
    day.solvePartOne();
}
