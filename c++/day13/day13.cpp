#include <iostream>
#include <sstream>
#include <vector>

#include "../AocProblem.h"

using std::string, std::vector, std::cout;

class Day13 : public AocProblem {
   public:
    void solvePartOne() {
        solve();
        cout << "Part one: " << silver << "\n";
    }

    void solvePartTwo() {
        solve();
        cout << "Part two: " << gold << "\n";
    }

    int silver;
    int gold;
    bool silverSolved = false;
    bool goldSolved = false;

    void solve() {
        if (silverSolved || goldSolved) {
            return;
        }

        string line;
        int lineNumber = 0;
        vector<vector<string>> patterns;

        vector<string> pattern;
        while (std::getline(std::cin, line)) {
            if (line.size() == 0) {
                patterns.push_back(pattern);
                pattern.clear();
                continue;
            }
            pattern.push_back(line);
        }
        patterns.push_back(pattern);

        int sum = 0;
        for (const auto& pattern : patterns) {
            int score = findReflectionScore(pattern);
            sum += score;
        }
        cout<< sum << "\n";
        silver = sum;

        sum = 0;
        for (const auto& pattern : patterns) {
            int score = findReflectionScoreWithSmudge(pattern);
            sum += score;
        }
        gold = sum;

        silverSolved = true;
        goldSolved = true;
    }

    int findReflectionScoreWithSmudge(const vector<string>& pattern){
        int vertical = findVerticalReflectionWithSmudge(pattern);
        int horizontal = findVerticalReflectionWithSmudge(transpose(pattern));

        return vertical * 100 + horizontal;;
    }

    int findReflectionScore(const vector<string>& pattern){
        int vertical = findVerticalReflection(pattern);
        int horizontal = findVerticalReflection(transpose(pattern));

        return vertical * 100 + horizontal;;
    }


    vector<string> transpose(const vector<string>& data) {
        vector<string> result(data[0].size(), "");

        for(int i = 0; i < data[0].size(); i++){
            for(int j = 0; j < data.size(); j ++){
                result[i] += data[j][i];
            }
        }

        return result;
    }

    bool stringAlmostEqual(const string& a, const string& b, int maxCharactersDiffering = 1){
        int notMatchingCount = 0;
        if(a.size() != b.size()){
            throw std::invalid_argument("strings must be the same size");
        }
        for(int i = 0; i < a.size() ; i++){
            if(a[i] != b[i]){
                notMatchingCount++;
            }
        }
        return notMatchingCount <= maxCharactersDiffering;
    }

    int findVerticalReflectionWithSmudge(const vector<string>& pattern){
        for (int line = 1; line < pattern.size(); line++) {
            bool possibleReflection = true;
            bool smudgeUsed = false;
            

            for (int j = 0; (line - j - 1) >= 0 && (line + j) < pattern.size();
                 j++) {
                if (pattern[line - j - 1] != pattern[line + j]) {
                    if(smudgeUsed){
                        possibleReflection = false;
                        break;
                    }
                    else{
                        if(stringAlmostEqual(pattern[line - j - 1], pattern[line + j])){
                            smudgeUsed = true;
                        }
                        else{
                            possibleReflection = false;
                            break;
                        }
                    }
                }
            }
            if (possibleReflection && smudgeUsed) {
                return line;
            }
        }
        return 0;
    }


    int findVerticalReflection(const std::vector<std::string>& pattern) {
        for (int line = 1; line < pattern.size(); line++) {
            bool possibleReflection = true;

            for (int j = 0; (line - j - 1) >= 0 && (line + j) < pattern.size();
                 j++) {
                if (pattern[line - j - 1] != pattern[line + j]) {
                    possibleReflection = false;
                    break;
                }
            }
            if (possibleReflection) {
                return line;
            }
        }
        return 0;
    }
};

int main() {
    Day13 day;
    day.solvePartTwo();
}