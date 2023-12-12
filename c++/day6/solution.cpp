#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string line;
    std::string word;
    std::vector<u_long> raceDurations;
    std::vector<u_long> raceRecords;

    std::getline(std::cin, line);
    std::stringstream ss(line);
    ss.ignore(line.length(), ':');

    std::string totalInt = "";
    while (ss >> word) {
        totalInt += word;
    }
    std::cout << totalInt << "\n";
    raceDurations.push_back(stoul(totalInt));

    std::getline(std::cin, line);
    ss = std::stringstream(line);

    ss.ignore(line.length(), ':');

    totalInt = "";
    while (ss >> word) {
        totalInt += word;
    }
    std::cout << totalInt << "\n";
    raceRecords.push_back(stoul(totalInt));

    // h = holdTime d = distanceTraveled r = currentRecord t = time
    // distance = h (t-h) = ht - h^2
    // ht - h^2 -r > 0
    // -h^2 + ht -r > 0     a = -1 b = t c = -r
    // determinant = t^2 - 4r
    // solution1 = -t + sqrt (t^2 - 4r) / -2
    long result = 1;

    for (int i = 0; i < raceRecords.size(); i++) {
        long double time = raceDurations[i];
        long double record = raceRecords[i];

        long double solutionOne =
            (time - sqrt(time * time - 4 * record)) / (1.99999999999999);
        long double solutionTwo =
            (time + sqrt(time * time - 4 * record)) / (2.00000000000001);

        std::cout << solutionOne << " x2: " << solutionTwo << '\n';
        int length = floor(solutionTwo) - ceil(solutionOne) + 1;
        result *= length;
    }
    std::cout << result;
}
