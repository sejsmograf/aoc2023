#include <iostream>
#include <string>
#define SEJSMO 9

int main() {
    std::string line;
    int sumPartOne = 0;
    int sumPartTwo = 0;

    std::string numbers[SEJSMO] = {"one", "two",   "three", "four", "five",
                                   "six", "seven", "eight", "nine"};

    while (std::getline(std::cin, line)) {
        int left = 0;
        int leftmostIndex = -1;
        int rightmostIndex = INT32_MAX;
        int right = 0;

        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                if (left == 0) {
                    left = line[i] - 0x30;
                    leftmostIndex = i;
                }
                right = line[i] - 0x30;
                rightmostIndex = i;
            }
        }

        sumPartOne += left * 10 + right;

        for (int i = 0; i < SEJSMO; i++) {
            int leftFind = line.find(numbers[i]);
            int rightFind = line.rfind(numbers[i]);
            if (leftFind < leftmostIndex && leftFind != -1) {
                left = i + 1;
                leftmostIndex = leftFind;
            }
            if (rightFind > rightmostIndex) {
                right = i + 1;
                rightmostIndex = rightFind;
            }
        }
        sumPartTwo += left * 10 + right;
    }
    std::cout << "Part one: " << sumPartOne << "\n";
    std::cout << "Part two: " << sumPartTwo;
}