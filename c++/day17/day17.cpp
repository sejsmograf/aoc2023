#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../AocProblem.h"

class Day17 : public AocProblem {
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
    }

    void bfs(std::vector<std::vector<int>>& distances,
             std::vector<std::vector<std::pair<int, int>>>& previous, int y,
             int x) {
        distances[y][x] = 0;
    }
};

int main() {
    Day17 day;
    day.solvePartOne();
}
