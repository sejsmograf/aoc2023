#include <memory>
#include <vector>

#include "day1/day1.cpp"

class ProblemManager {
   public:
    ProblemManager() { aocProblems.push_back(std::make_unique<Day1>()); }
    solve(const std::string& problemName) {}

   private:
    std::vector<std::unique_ptr<AocProblem>> aocProblems;
};

int main(int argc) {
    ProblemManager problemManager;
    problemManager
}
