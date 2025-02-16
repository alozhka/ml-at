#include <climits>
#include <iostream>
#include <ostream>
#include <stack>
#include <vector>

class TimberCutter {
public:
  static int Cut(const int length, const int timesToCut) {
    int minCost = INT_MAX;
    std::vector timbers = {length};
    // [timbers, times, cost]
    std::stack<std::tuple<std::vector<int>, int, int>> dataStack = {};
    dataStack.emplace(timbers, timesToCut, 0);

    while (!dataStack.empty()) {
      auto [timbers, times, cost] = dataStack.top();
      dataStack.pop();

      if (times == 0) {
        if (cost < minCost) {
          minCost = cost;
        }
        continue;
      }

      for (int i = 0; i < timbers.size(); i++) {
        for (int j = 1; j < timbers[i]; j++) {
          int left = j;
          int right = timbers[i] - j;

          std::vector<int> newTimbers = {};
          std::ranges::copy(timbers, std::back_inserter(newTimbers));
          auto it = newTimbers.erase(newTimbers.begin() + i);
          newTimbers.insert(it, {left, right});

          dataStack.emplace(newTimbers, times - 1, cost + timbers[i]);
        }
      }
    }

    return minCost;
  }
};

int main(int argc, char *argv[]) {
  std::cout << TimberCutter::Cut(std::atoi(argv[1]), std::atoi(argv[2])) << std::endl;
}
