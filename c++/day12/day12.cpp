#include "../AocProblem.h"
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class Day12 : AocProblem {
  public:
    void solvePartOne() override {
        calculateSolution();
        std::cout << "Part one: " << silver;
    }
    void solvePartTwo() override {}

  private:
    int silver;
    int gold;
    bool silverSolved = false;
    bool goldSolved = false;

    void calculateSolution() {
        if (silverSolved || goldSolved) {
            return;
        }
        std::string line;
        std::string word;
        std::vector<std::string> springs;
        std::vector<std::vector<int>> requiredGroups;

        int lineCount = 0;
        while (std::getline(std::cin, line)) {
            std::stringstream ss(line);
            std::vector<int> required;

            ss >> word;
            springs.push_back(word);

            while (std::getline(ss, word, ',')) {
                required.push_back(stoi(word));
            }
            lineCount++;
            requiredGroups.push_back(required);
        }

        std::vector<std::string> newSprings;
        std::vector<std::vector<int>> newGroups;

        for (int i = 0; i < springs.size(); i++) {
            std::string newSpring = "";
            std::vector<int> newGroup;
            for (int j = 0; j < 5; j++) {
                newSpring += springs[i];
                if(j!=4){
                    newSpring+='?';
                }
                for (int k = 0; k < requiredGroups[i].size(); k++) {
                    newGroup.push_back(requiredGroups[i][k]);
                }
            }
            newSprings.push_back(newSpring);
            newGroups.push_back(newGroup);
        }

        for (int i = 0; i < newGroups.size(); i++) {
            std::cout<<newSprings[i]<<"   ";
            for (const auto mandzio : newGroups[i]) {
                std::cout << mandzio << ' ';
            }
            std::cout<<'\n';
        }

        unsigned long long sum = 0;
        for (int i = 0; i < springs.size(); i++) {
            std::cout << "Index: " << i << " of: " << springs.size() << '\n';
            sum += gigachadBruteForce(newSprings[i], 0, newGroups[i]);
        }
        std::cout << sum;
    }

    std::vector<std::pair<int, int>> getCharacterGroups(std::string line,
                                                        char c) {
        std::vector<std::pair<int, int>> brokenGroups;
        int startingIndex = 0;
        int groupLength = 0;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == c) {
                if (groupLength == 0) {
                    startingIndex = i;
                }
                groupLength++;
            } else {
                if (groupLength != 0) {
                    brokenGroups.push_back({startingIndex, groupLength});
                    groupLength = 0;
                }
            }
        }
        return brokenGroups;
    }

    int gigachadBruteForce(std::string& currentCombination, int index,
                           const std::vector<int> &groups) {
        if (index == currentCombination.size()) {
            return checkSolution(currentCombination, groups);
        }
        int count = 0;
        if (currentCombination[index] == '?') {
            currentCombination[index] = '#';
            count += gigachadBruteForce(currentCombination, index + 1, groups);

            currentCombination[index] = '.';
            count += gigachadBruteForce(currentCombination, index + 1, groups);

            currentCombination[index] = '?';
        } else {
            count += gigachadBruteForce(currentCombination, index + 1, groups);
        }
        return count;
    }

    bool checkSolution(const std::string &solution,
                       const std::vector<int> &requiredGroups) {
        int groupLength = 0;
        int groupIndex = 0;

        for (int i = 0; i < solution.length(); i++) {
            if (solution[i] == '#') {
                groupLength++;
            } else {
                if (groupLength != 0) {
                    if (groupIndex >= requiredGroups.size() ||
                        groupLength != requiredGroups[groupIndex]) {
                        return false;
                    }
                    groupLength = 0;
                    groupIndex++;
                }
            }
        }

        // Check the last group
        if (groupLength != 0) {
            if (groupIndex >= requiredGroups.size() ||
                groupLength != requiredGroups[groupIndex]) {
                return false;
            }
            groupIndex++; // Increment groupIndex here
        }

        // Ensure that all required groups have been matched
        return groupIndex == requiredGroups.size();
    }

    int getPossiblePositions(std::string line, int startingIndex,
                             const std::vector<int> &groupLengths,
                             int groupIndex,
                             std::set<std::string> &foundSolutions) {
        std::stringstream ss(line);
        int length = groupLengths[groupIndex];
        bool last = (groupIndex == groupLengths.size() - 1);
        bool first = (groupIndex == 0);
        std::cout << "seraching for length: " << length
                  << "   in line: " << line << "\n";

        int count = 0;
        for (int i = startingIndex; i <= (int)(line.size() - length); i++) {
            bool isPossibleSolution = true;
            bool originalIntact = false;
            std::string modifiedLine(line);
            for (int j = i; j < i + length; j++) {
                if (line[j] != '?' && line[j] != '#') {
                    isPossibleSolution = false;
                    break;
                }
            }
            if (isPossibleSolution) {
                if (!last && (i + length + 1) < line.size() &&
                    line[i + length] != '#' && (i == 0 || line[i - 1] != '#')) {
                    std::cout << "found length at " << i << "\n";
                    for (int j = i; j < i + length; j++) {
                        if (modifiedLine[j] != '#') {
                            originalIntact = true;
                        }
                        modifiedLine[j] = '#';
                    }
                    std::cout << "ENTERING ANOTHER LOOP WITH LINE "
                              << modifiedLine << " searching for "
                              << groupIndex + 1 << " : "
                              << groupLengths[groupIndex + 1] << "\n";
                    count += getPossiblePositions(modifiedLine, i + length + 1,
                                                  groupLengths, groupIndex + 1,
                                                  foundSolutions);
                    if (originalIntact) {
                        break;
                    }
                }
                if (last && line[i + length] != '#' &&
                    (i == 0 || line[i - 1] != '#')) {
                    for (int j = i; j < i + length; j++) {
                        modifiedLine[j] = '#';
                    }
                    std::cout << modifiedLine << '\n';
                    count++;
                }
            }
        }
        std::cout << "\n\n";

        return count;
    }
};

int main() {
    Day12 day;
    day.solvePartOne();
    return 0;
}