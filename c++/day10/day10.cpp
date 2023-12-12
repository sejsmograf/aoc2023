#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../AocProblem.h"

class Day10 : public AocProblem {
  public:
    void solvePartOne() override {
        calculateSolution();
        std::cout << "Part one: " << silver << "\n";
    }

    void solvePartTwo() override {}

  private:
    int silver;
    int gold;
    bool silverSolved = false;
    bool goldSolved = false;

    void calculateSolution() {
        std::string line;
        std::vector<std::string> areaMap;

        int lineNumber = 0;
        while (std::getline(std::cin, line)) {
            areaMap.push_back(line);
        }

        std::pair<int, int> startingPos;
        for (int i = 0; i < areaMap.size(); i++) {
            for (int j = 0; j < areaMap[0].size(); j++) {
                if (areaMap[i][j] == 'S') {
                    startingPos = {i, j};
                    break;
                }
            }
        }
        std::cout << "Start: " << startingPos.first << "  "
                  << startingPos.second << '\n';

        int pipeCount =
            bfsArea(areaMap, {startingPos.first, startingPos.second + 1});

        std::cout << "Part one: " << ceil(pipeCount / 2);
    }

    std::map<char, std::pair<std::pair<int, int>, std::pair<int, int>>>
        pipeConnections = {{'|', {{-1, 0}, {1, 0}}}, {'-', {{0, -1}, {0, 1}}},
                           {'L', {{-1, 0}, {0, 1}}}, {'J', {{-1, 0}, {0, -1}}},
                           {'7', {{1, 0}, {0, -1}}}, {'F', {{1, 0}, {0, 1}}}};

    std::pair<std::pair<int, int>, std::pair<int, int>>
    getAdjacentTiles(int y, int x, char pipe) {
        auto connections = pipeConnections[pipe];
        return {{y + connections.first.first, x + connections.first.second},
                {y + connections.second.first, x + connections.second.second}};
    }

    int bfsArea(std::vector<std::string> &area, std::pair<int, int> location) {
        std::vector<std::vector<bool>> visited(
            area.size(), std::vector<bool>(area[0].size(), false));

        std::queue<std::pair<int, int>> q;
        q.push(location);

        int count = 0;
        while (!q.empty()) {
            count++;
            std::pair<int, int> front = q.front();
            std::pair<std::pair<int, int>, std::pair<int, int>>
                neighborCoordinates = getAdjacentTiles(
                    front.first, front.second, area[front.first][front.second]);
            visited[front.first][front.second] = true;
            q.pop();

            auto neighborOne = neighborCoordinates.first;
            auto neighborTwo = neighborCoordinates.second;

            if (!visited[neighborOne.first][neighborOne.second]) {
                q.push(neighborOne);
            }
            if (!visited[neighborTwo.first][neighborTwo.second]) {
                q.push(neighborTwo);
            }
        }

        int fieldsInside = 0;
        area[107][110] = '|';

        for (int y = 0; y < area.size(); y++) {
            bool inside = false;
            char previousDirectionChange = 'x';
            for (int x = 0; x < area[0].size(); x++) {
                char charAt = area[y][x];
                if (visited[y][x] && charAt != '-') {
                    switch (charAt) {
                    case '|':
                        inside = !inside;
                        break;
                    case 'J':
                        if (previousDirectionChange == 'F') {
                            inside = !inside;
                        }
                        break;
                    case '7':
                        if (previousDirectionChange == 'L') {
                            inside = !inside;
                        }
                        break;
                    }

                    std::cout << "Encountered " << charAt << " at line "
                              << y + 1 << " char " << x + 1
                              << " currently inside: " << inside << "\n";

                    previousDirectionChange = charAt;
                } else if (inside && !visited[y][x]) {
                    area[y][x] = 'I';
                    std::cout << "FOUND INSIDE :" << y + 1 << " " << x + 1
                              << "\n";
                    fieldsInside++;
                }
            }
            std::cout << "\n\n\n";
        }

        for (int i = 0; i < area.size(); i++) {
            for (int j = 0; j < area[0].size(); j++) {
                if (visited[i][j]) {
                    std::cout << area[i][j];
                } else {
                    std::cout << ' ';
                }
            }
        }

        std::cout << "Fields inside: \0\0\0\0\0\0" << fieldsInside << "\n";
        return count;
    };
};

int main() {
    Day10 day;
    day.solvePartOne();
}
