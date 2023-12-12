#include "../AocProblem.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Day11 : public AocProblem {
  public:
    void solvePartOne() override {
        calculateSolution();
        std::cout << "Part one: " << silver << "\n";
    }
    void solvePartTwo() override {
        calculateSolution();
        std::cout << "Part two: " << gold << "\n";
    }

  private:
    int silver;
    unsigned long long gold;
    bool silverSolved = false;
    bool goldSolved = false;

    void calculateSolution() {
        if (silverSolved == true || goldSolved == true) {
            return;
        }
        std::string line;
        std::vector<std::string> image;
        std::vector<std::pair<int, int>> galaxies;

        int rowNumber = 0;
        while (std::getline(std::cin, line)) {
            image.push_back(line);
            for (int x = 0; x < line.size(); x++) {
                if (line[x] == '#') {
                    galaxies.push_back({rowNumber, x});
                }
            }
            rowNumber++;
        }

        std::vector<int> emptyRows = getEmptyRows(image);
        std::vector<int> emptyColumns = getEmptyColumns(image);

        unsigned long long totalDistance = 0;
        unsigned long long EXPANSION_LEVEL = 1000000;

        for (int i = 1; i < galaxies.size(); i++) {
            std::pair<int, int> currentGalaxy = galaxies[i - 1];
            for (int j = i; j < galaxies.size(); j++) {
                totalDistance +=
                    calculateDistance(currentGalaxy, galaxies[j]) +
                    (EXPANSION_LEVEL - 1) *
                        (getExpandedColumnsBetween(emptyColumns, currentGalaxy,
                                                   galaxies[j]) +
                         getExpandedRowsBetween(emptyRows, currentGalaxy,
                                                galaxies[j]));
            }
        }
        gold = totalDistance;
        goldSolved = true;

        totalDistance = 0;
        EXPANSION_LEVEL = 2;

        for (int i = 1; i < galaxies.size(); i++) {
            std::pair<int, int> currentGalaxy = galaxies[i - 1];
            for (int j = i; j < galaxies.size(); j++) {
                totalDistance +=
                    calculateDistance(currentGalaxy, galaxies[j]) +
                    (EXPANSION_LEVEL - 1) *
                        (getExpandedColumnsBetween(emptyColumns, currentGalaxy,
                                                   galaxies[j]) +
                         getExpandedRowsBetween(emptyRows, currentGalaxy,
                                                galaxies[j]));
            }
        }
        silver = totalDistance;
        silverSolved = true;
    }

    std::vector<int> getEmptyRows(const std::vector<std::string> &image) {
        std::vector<int> result;
        for (int y = 0; y < image.size(); y++) {
            bool isEmpty = true;
            for (int x = 0; x < image[0].size(); x++) {
                if (image[y][x] == '#') {
                    isEmpty = false;
                    break;
                }
            }
            if (isEmpty) {
                result.push_back(y);
            }
        }
        return result;
    }

    std::vector<int> getEmptyColumns(const std::vector<std::string> &image) {
        std::vector<int> result;
        for (int x = 0; x < image[0].size(); x++) {
            bool isEmpty = true;
            for (int y = 0; y < image.size(); y++) {
                if (image[y][x] == '#') {
                    isEmpty = false;
                    break;
                }
            }
            if (isEmpty) {
                result.push_back(x);
            }
        }
        return result;
    }

    int calculateDistance(std::pair<int, int> locationOne,
                          std::pair<int, int> locationTwo) {
        return abs(locationOne.first - locationTwo.first) +
               abs(locationOne.second - locationTwo.second);
    }

    int getExpandedColumnsBetween(const std::vector<int> &emptyColumns,
                                  std::pair<int, int> locationOne,
                                  std::pair<int, int> locationTwo) {
        int upperBound, lowerBound;
        if (locationOne.second >= locationTwo.second) {
            upperBound = locationOne.second;
            lowerBound = locationTwo.second;
        } else {
            upperBound = locationTwo.second;
            lowerBound = locationOne.second;
        }
        auto lowerIter = std::lower_bound(emptyColumns.begin(),
                                          emptyColumns.end(), lowerBound);
        auto upperIter = std::upper_bound(emptyColumns.begin(),
                                          emptyColumns.end(), upperBound);
        return std::distance(lowerIter, upperIter);
    }

    int getExpandedRowsBetween(const std::vector<int> &emptyRows,
                               std::pair<int, int> locationOne,
                               std::pair<int, int> locationTwo) {
        int upperBound, lowerBound;
        if (locationOne.first >= locationTwo.first) {
            upperBound = locationOne.first;
            lowerBound = locationTwo.first;
        } else {
            upperBound = locationTwo.first;
            lowerBound = locationOne.first;
        }
        auto lowerIter =
            std::lower_bound(emptyRows.begin(), emptyRows.end(), lowerBound);
        auto upperIter =
            std::upper_bound(emptyRows.begin(), emptyRows.end(), upperBound);
        return std::distance(lowerIter, upperIter);
    }
};

int main() {
    Day11 day;
    day.solvePartOne();
    day.solvePartTwo();
}