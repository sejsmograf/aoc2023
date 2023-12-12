#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../AocProblem.h"

class Day9 : public AocProblem {
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
    unsigned long long silver;
    long long gold;
    bool silverSolved = false;
    bool goldSolved = false;

    void calculateSolution() {
        if (silverSolved || goldSolved) {
            return;
        }
        std::string line;

        std::vector<std::vector<long long>> histories;

        while (std::getline(std::cin, line)) {
            std::vector<long long> currentHistory;
            std::string word;
            std::stringstream ss(line);
            while (ss >> word) {
                currentHistory.push_back(stoul(word));
            }
            histories.push_back(currentHistory);
        }

        std::vector<std::vector<std::vector<long long>>> allReducedHistories;
        for (int i = 0; i < histories.size(); i++) {
            std::vector<std::vector<long long>> reducedHistory;
            bool allZeroes;
            reducedHistory.push_back(histories[i]);
            int historyDepth = 0;
            while (true) {
                allZeroes = true;
                for (long number : reducedHistory[historyDepth]) {
                    if (number != 0) {
                        allZeroes = false;
                        break;
                    }
                }
                if (allZeroes) {
                    break;
                }
                std::vector<long long> reducedHistoryStep;
                for (int num = 1; num < reducedHistory[historyDepth].size();
                     num++) {
                    reducedHistoryStep.push_back(
                        reducedHistory[historyDepth][num] -
                        reducedHistory[historyDepth][num - 1]);
                }
                reducedHistory.push_back(reducedHistoryStep);
                historyDepth++;
            }
            allReducedHistories.push_back(reducedHistory);
        }

        unsigned long long innerSilver = 0;
        for (const auto& reducedHistory : allReducedHistories) {
            innerSilver += calculateNextHistoryNumber(
                reducedHistory, 0, reducedHistory.size() - 1);
        }
        silver = innerSilver;
        silverSolved = true;

        long long innerGold = 0;
        for (const auto& reducedHistory : allReducedHistories) {
            innerGold += calculatePreviousHistoryNumber(
                reducedHistory, 0, reducedHistory.size() - 1);
        }
        gold = innerGold;
        goldSolved = true;
    }

    long calculateNextHistoryNumber(
        const std::vector<std::vector<long long>>& reducedHistory,
        int historyDepth, int maxDepth) const {
        int length = reducedHistory[historyDepth].size();
        int lastElement = reducedHistory[historyDepth][length - 1];
        if (historyDepth == maxDepth) {
            return 0;
        }
        return lastElement + calculateNextHistoryNumber(
                                 reducedHistory, historyDepth + 1, maxDepth);
    }

    long calculatePreviousHistoryNumber(
        const std::vector<std::vector<long long>>& reducedHistory,
        int historyDepth, int maxDepth) const {
        int firstElement = reducedHistory[historyDepth][0];
        if (historyDepth == maxDepth) {
            return 0;
        }
        return firstElement - calculatePreviousHistoryNumber(
                                  reducedHistory, historyDepth + 1, maxDepth);
    }
};

int main() {
    Day9 day;
    day.solvePartOne();
    return 0;
}