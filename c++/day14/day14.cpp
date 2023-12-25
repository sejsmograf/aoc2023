#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../AocProblem.h"

class Day14 : public AocProblem {
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
        std::vector<std::string> inputSilver;
        std::vector<std::string> inputGold;

        while (std::getline(std::cin, line)) {
            inputSilver.push_back(line);
            inputGold.push_back(line);
        }

        tiltDish(inputSilver, {-1, 0});
        silver = calculateScore(inputSilver);

        std::set<std::vector<std::string>> beforeCycleStates;
        int tiltsBeforeCycle;
        for (unsigned long long i = 0; i < 1000; i++) {
            if (beforeCycleStates.find(inputGold) != beforeCycleStates.end()) {
                tiltsBeforeCycle = i;
                break;
            }
            beforeCycleStates.insert(inputGold);
            tiltDishCycle(inputGold);
        }

        std::set<std::vector<std::string>> insideCycleStates;
        int cycleLength;

        for (unsigned long long i = 0; i < 1000; i++) {
            if (insideCycleStates.find(inputGold) != insideCycleStates.end()) {
                cycleLength = i;
                break;
            }
            insideCycleStates.insert(inputGold);
            tiltDishCycle(inputGold);
        }

        for (int i = 0; i < ((1000000000 - tiltsBeforeCycle) % cycleLength);
             i++) {
            tiltDishCycle(inputGold);
        }

        std::cout << "score: " << calculateScore(inputGold) << "\n";
        std::cout << "titls till cycle: " << tiltsBeforeCycle << "\n";
        std::cout << "cycle lengthw: " << cycleLength << "\n";
    }

    int calculateScore(const std::vector<std::string>& data) {
        int score = 0;

        for (int i = 1; i <= data.size(); i++) {
            score += i * countOccurances(data[data.size() - i], 'O');
        }
        return score;
    }

    int countOccurances(const std::string& str, char targetChar) {
        int count = 0;
        for (char ch : str) {
            if (ch == targetChar) {
                count++;
            }
        }
        return count;
    }

    void tiltDishCycle(std::vector<std::string>& dish) {
        tiltDish(dish, {-1, 0});
        tiltDish(dish, {0, -1});
        tiltDish(dish, {1, 0});
        tiltDish(dish, {0, 1});
    }

    void tiltDish(std::vector<std::string>& dish,
                  std::pair<int, int> direction) {
        if (direction.first == -1 || direction.second == -1) {
            for (int y = 0; y < dish.size(); y++) {
                for (int x = 0; x < dish[y].size(); x++) {
                    if (dish[y][x] == 'O') {
                        std::pair<int, int> newLocation =
                            rollRock(dish, direction, {y, x});
                        if (newLocation.first != y || newLocation.second != x) {
                            dish[y][x] = '.';
                            dish[newLocation.first][newLocation.second] = 'O';
                        }
                    }
                }
            }
        } else {
            for (int y = dish.size() - 1; y >= 0; y--) {
                for (int x = dish[y].size() - 1; x >= 0; x--) {
                    if (dish[y][x] == 'O') {
                        std::pair<int, int> newLocation =
                            rollRock(dish, direction, {y, x});
                        if (newLocation.first != y || newLocation.second != x) {
                            dish[y][x] = '.';
                            dish[newLocation.first][newLocation.second] = 'O';
                        }
                    }
                }
            }
        }
    }

    std::pair<int, int> rollRock(const std::vector<std::string>& dish,
                                 std::pair<int, int> direction,
                                 std::pair<int, int> position) {
        std::pair<int, int> newPosition = position;
        while (newPosition.first + direction.first >= 0 &&
               newPosition.first + direction.first < dish.size() &&
               newPosition.second + direction.second >= 0 &&
               newPosition.second + direction.second < dish[0].size()) {
            if (dish[newPosition.first + direction.first]
                    [newPosition.second + direction.second] == '.') {
                newPosition.first += direction.first;
                newPosition.second += direction.second;
            } else {
                break;
            }
        }
        return newPosition;
    };
};

int main() {
    Day14 day;
    day.solvePartOne();
}
