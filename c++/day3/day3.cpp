#include <iostream>
#include <sstream>
#include <vector>

std::pair<int, int> getAdjacentIntFromData(
    int y, int x, const std::vector<std::string>& data) {
    int leftIndex = x;
    int rightIndex = x;
    while (isdigit(data[y][leftIndex - 1])) {
        if (leftIndex == 0 || leftIndex == 1) {
            leftIndex = 0;
            break;
        }
        --leftIndex;
    }
    while (isdigit(data[y][rightIndex])) {
        if (rightIndex == (data[0].length() - 1)) {
            break;
        }
        ++rightIndex;
    }

    return std::pair<int, int>{leftIndex,
                               stoi(data[y].substr(leftIndex, rightIndex))};
}

std::pair<int, int> getAllAdjacentIntsSumAndRatio(
    int y, int x, const std::vector<std::string>& data) {
    int sum = 0;
    int leftIndex = -1;
    int found = 0;
    int ratio = 1;

    if (y > 0 && x > 0 && isdigit(data[y - 1][x - 1])) {
        std::pair<int, int> foundInteger =
            getAdjacentIntFromData(y - 1, x - 1, data);
        sum += foundInteger.second;
        found++;
        ratio *= foundInteger.second;
        leftIndex = foundInteger.first;
    }

    if (y > 0 && isdigit(data[y - 1][x])) {
        std::pair<int, int> foundInteger =
            getAdjacentIntFromData(y - 1, x, data);
        if (foundInteger.first != leftIndex) {
            sum += foundInteger.second;
            ratio *= foundInteger.second;
            found++;
        }
        leftIndex = foundInteger.first;
    }

    if (y > 0 && x < data[0].length() && isdigit(data[y - 1][x + 1])) {
        std::pair<int, int> foundInteger =
            getAdjacentIntFromData(y - 1, x + 1, data);
        if (foundInteger.first != leftIndex) {
            sum += foundInteger.second;
            ratio *= foundInteger.second;
            found++;
        }
        leftIndex = foundInteger.first;
    }

    if (x > 0 && isdigit(data[y][x - 1])) {
        std::pair<int, int> foundInteger =
            getAdjacentIntFromData(y, x - 1, data);
        sum += foundInteger.second;
        ratio *= foundInteger.second;
        found++;
    }

    if (x < data[0].size() && isdigit(data[y][x + 1])) {
        std::pair<int, int> foundInteger =
            getAdjacentIntFromData(y, x + 1, data);
        sum += foundInteger.second;
        ratio *= foundInteger.second;
        found++;
    }

    leftIndex = -1;

    if (y < data.size() - 1 && x > 0 && isdigit(data[y + 1][x - 1])) {
        std::pair<int, int> foundInteger =
            getAdjacentIntFromData(y + 1, x - 1, data);
        leftIndex = foundInteger.first;
        ratio *= foundInteger.second;
        found++;
        sum += foundInteger.second;
    }

    if (y < data.size() - 1 && isdigit(data[y + 1][x])) {
        std::pair<int, int> foundInteger =
            getAdjacentIntFromData(y + 1, x, data);
        if (foundInteger.first != leftIndex) {
            ratio *= foundInteger.second;
            sum += foundInteger.second;
            found++;
        }
        leftIndex = foundInteger.first;
    }

    if (y < data.size() - 1 && x < data[0].length() &&
        isdigit(data[y + 1][x + 1])) {
        std::pair<int, int> foundInteger =
            getAdjacentIntFromData(y + 1, x + 1, data);
        if (foundInteger.first != leftIndex) {
            ratio *= foundInteger.second;
            sum += foundInteger.second;
            found++;
        }
        leftIndex = foundInteger.first;
    }
    if (found == 2) {
        return std::pair<int, int>(ratio, sum);
    } else {
        return std::pair<int, int>(0, sum);
    }
}

int main() {
    std::string line;
    std::vector<std::string> input;

    while (std::getline(std::cin, line)) {
        input.push_back(line);
    }

    int sumPartOne = 0;
    long sumPartTwo = 0;

    // Part One
    for (int line = 0; line < input.size(); line++) {
        for (int index = 0; index < input[0].size(); index++) {
            char ch = input[line][index];
            if (!isdigit(ch) && ch != '.') {
                sumPartOne +=
                    getAllAdjacentIntsSumAndRatio(line, index, input).second;
            }
            if (ch == '*') {
                sumPartTwo +=
                    getAllAdjacentIntsSumAndRatio(line, index, input).first;
            }
        }
    }
    std::cout << sumPartOne << "\n" << sumPartTwo;
}
