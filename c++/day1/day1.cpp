#include <iostream>
#include <string>

#include "../AocProblem.h"
#define SEJSMO 9

class Day1 : public AocProblem {
   public:
    void solvePartOne() override {
        calculateSolutions();
        std::cout << "partOne: " << silver << "\n";
    }
    void solvePartTwo() override {
        calculateSolutions();
        std::cout << "partTwo: " << gold << "\n";
    }

   private:
    int silver;
    int gold;
    bool solved = false;

    void calculateSolutions() {
        if (solved) {
            return;  // means the instance already has solution
        }
        std::string line;
        std::string numbers[SEJSMO] = {"one", "two",   "three", "four", "five",
                                       "six", "seven", "eight", "nine"};
        int innerSumPartOne = 0;
        int innerSumPartTwo = 0;
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

            innerSumPartOne += left * 10 + right;

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
            innerSumPartTwo += left * 10 + right;
        }
        silver = innerSumPartOne;
        gold = innerSumPartTwo;
        this->solved = true;
    }
};
