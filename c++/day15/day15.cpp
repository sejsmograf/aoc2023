#include <iostream>
#include <set>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <sstream>

#include "../AocProblem.h"


class Day15 : public AocProblem {
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

    void solve(){
        if(silverSolved || goldSolved){
            return;
        }
        std::string line;
        std::getline(std::cin, line);

        std::vector<std::string> sequences;
        std::string currentWord = "";
        for(int i = 0; i < line.size(); i++){
            if(line[i] == ','){
                sequences.push_back(currentWord);
                currentWord = "";
            }
            else{
                currentWord += line[i];
            }
        }
        sequences.push_back(currentWord);
        
        int sum = 0;
        for(const auto& word : sequences){
            sum+=calculateHashcode(word);
        }
        silver = sum;

        std::vector<std::vector<std::string>> lenses(256);
        std::vector<std::vector<int>> lengths(256);

        for(const auto& word : sequences){
            if(word.find('=') != std::string::npos){
                std::string lensLabel = word.substr(0,word.length() - 2);
                int boxCode = calculateHashcode(lensLabel);
                int lensLength = word[word.length() -1] - '0';
                bool found = false;
                for(int i = 0; i < lenses[boxCode].size(); i++){
                    if(lenses[boxCode][i] == lensLabel){
                        lengths[boxCode][i] = lensLength;
                        found = true;
                    }
                }
                if(!found){
                    lenses[boxCode].push_back(lensLabel);
                    lengths[boxCode].push_back(lensLength);
                }
            } else{
                std::string lensLabel = word.substr(0,word.length() - 1);
                int boxCode = calculateHashcode(lensLabel);
                for(int i = 0; i < lenses[boxCode].size(); i++){
                    if(lenses[boxCode][i] == lensLabel){
                        lenses[boxCode].erase(lenses[boxCode].begin() +i);
                        lengths[boxCode].erase(lengths[boxCode].begin() +i);
                    }
                }
            }
        }

        sum = 0;
        for(int i = 0; i < lenses.size(); i++){
            std::cout<<"Box " << i<<"\n";
            for(int j = 0; j < lenses[i].size(); j++){
                sum += (i+1) * (j+1) * lengths[i][j];
                std::cout<< "Lens: " << lenses[i][j] << " " << lengths[i][j]<<"\n";
            }
        }
        gold = sum;
    }


    int calculateHashcode(const std::string& data, int currentValue = 0,  int index = 0){
        currentValue += data[index];
        currentValue *= 17;
        currentValue %= 256;
        
        if(index == data.size() -1){
            return currentValue;
        }
        return calculateHashcode(data, currentValue, index + 1);
    }

};


int main() {
    Day15 day;
    day.solvePartTwo();
}
