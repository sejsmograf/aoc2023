#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define CARD_NUMBER 13
enum handTypes { HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE, FULL_HOUSE, FOUR, FIVE };

const char allCards[CARD_NUMBER] = {'J', '2', '3', '4', '5', '6', '7',
                                    '8', '9', 'T', 'Q', 'K', 'A'};

int calculateCardScore(const std::string& hand) {
    std::map<char, long> cardCounts;
    for (char card : hand) {
        cardCounts[card]++;
    }

    int maxCardCount = 0;

    for (const auto& count : cardCounts) {
        if (count.second > maxCardCount) {
            maxCardCount = count.second;
        }
    }

    std::cout << "romiar " << hand << " " << cardCounts.size()
              << " max: " << maxCardCount << "\n";
    int setSize = cardCounts.size();
    switch (cardCounts['J']) {
        case 0:
            switch (maxCardCount) {
                case 5:
                    return FIVE;
                case 4:
                    return FOUR;
                case 3:
                    if (setSize == 2) {
                        return FULL_HOUSE;
                    }
                    return THREE;
                case 2:
                    if (setSize == 3) {
                        return TWO_PAIR;
                    }
                    return ONE_PAIR;
                case 1:
                    return HIGH_CARD;
            }
        case 1:
            switch (maxCardCount) {
                case 4:
                    return FIVE;
                case 3:
                    return FOUR;
                case 2:
                    if (setSize == 3) {
                        return FULL_HOUSE;
                    }
                    return THREE;
                case 1:
                    return ONE_PAIR;
            }
        case 2:
            switch (maxCardCount) {
                case 3:
                    if (setSize == 2) {
                        return FIVE;
                    }
                case 2:
                    if (setSize == 3) {
                        return FOUR;
                    }
                    return THREE;
            }
        case 3:
            switch (maxCardCount) {
                case 3:
                    if (setSize == 2) {
                        return FIVE;
                    }
                    return FOUR;
            }
        case 4:
            switch (maxCardCount) {
                case 4:
                    return FIVE;
            }
        case 5:
            return FIVE;
    }

    return -1;
}

struct CustomComparator {
    bool operator()(const std::string& a, const std::string& b) const {
        if (calculateCardScore(a) != calculateCardScore(b)) {
            return calculateCardScore(a) < calculateCardScore(b);
        }
        for (int i = 0; i < a.size(); i++) {
            int cardAIndex;
            int cardBIndex;
            for (int j = 0; j < CARD_NUMBER; j++) {
                if (allCards[j] == a[i]) {
                    cardAIndex = j;
                }
                if (allCards[j] == b[i]) {
                    cardBIndex = j;
                }
            }
            if (cardAIndex != cardBIndex) {
                return cardAIndex < cardBIndex;
            }
        }
        throw std::invalid_argument(
            "AddPositiveIntegers arguments must be positive");
    }
};

int main() {
    std::string line;
    std::string word;
    std::map<std::string, int, CustomComparator> cardSet;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        ss >> word;
        std::string card = word;

        ss >> word;
        int bidAmount = stol(word);

        cardSet[card] = bidAmount;
    }

    u_long totalBidPartOne = 0;
    int cardRank = 1;
    for (const auto& card : cardSet) {
        std::cout << card.first << " " << calculateCardScore(card.first)
                  << '\n';
        totalBidPartOne += (card.second * cardRank);
        cardRank++;
    }

    std::cout << "Part one: " << totalBidPartOne;

    return 0;
}