#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct SourceToDestinationRange {
    uint64_t destinationStart;
    uint64_t sourceStart;
    uint64_t length;
};

uint64_t processSeedThroughMaps(
    uint64_t seed, const std::vector<SourceToDestinationRange>& maps) {
    for (const auto& map : maps) {
        if (seed < map.sourceStart + map.length && seed >= map.sourceStart) {
            return seed - (map.sourceStart - map.destinationStart);
        }
    }
    return seed;
}

int main() {
    std::vector<uint64_t> seeds;

    std::string line;
    std::string word;

    std::getline(std::cin, line);
    std::stringstream ss(line);
    ss.ignore(line.length(), ':');

    while (ss >> word) {
        seeds.push_back(stol(word));
    }

    std::vector<std::vector<SourceToDestinationRange>> map;
    std::vector<SourceToDestinationRange> currentMap;
    std::getline(std::cin, line);
    std::getline(std::cin, line);

    while (std::getline(std::cin, line)) {
        if (line.length() == 0) {
            map.push_back(currentMap);
            currentMap.clear();
            std::getline(std::cin, line);
            continue;
        }

        std::stringstream ss(line);
        ss >> word;
        uint64_t destinationStart = stol(word);
        ss >> word;
        uint64_t sourceStart = stol(word);
        ss >> word;
        uint64_t length = stol(word);

        ;
        currentMap.push_back({destinationStart, sourceStart, length});
    }
    map.push_back(currentMap);

    std::vector<uint64_t> seedDestinations;

    for (uint64_t seed : seeds) {
        for (const auto& vec : map) {
            seed = processSeedThroughMaps(seed, vec);
        }
        seedDestinations.push_back(seed);
    }

    uint64_t minPartOne = UINT64_MAX;

    for (uint64_t dest : seedDestinations) {
        if (dest < minPartOne) {
            minPartOne = dest;
        }
    }
    std::cout << minPartOne << '\n';

    uint64_t minPartTwo = UINT64_MAX;

    for (int i = 0; i < seeds.size(); i += 2) {
        std::cout << "Group " << i << ": " << seeds[i] << " to "
                  << (seeds[i + 1] + seeds[i]) << "\n";
        for (uint64_t seed = seeds[i]; seed < (seeds[i] + seeds[i + 1]);
             seed++) {
            if (seed % 1048576 == 0) {
                std::cout << seed << "\n";
            }
            uint64_t plantedSeed = seed;
            for (const auto& vec : map) {
                plantedSeed = processSeedThroughMaps(plantedSeed, vec);
            }
            if (plantedSeed < minPartTwo) {
                std::cout << "NEW MIN: " << plantedSeed << "\n";
                minPartTwo = plantedSeed;
            }
        }
    }

    std::cout << "Part two: " << minPartTwo;
}
