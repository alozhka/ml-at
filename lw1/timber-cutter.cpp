#include <climits>
#include <iostream>
#include <ostream>
#include <vector>

class TimberCutter
{
  static void CutInternal(std::vector<int>& timbers, const int times, int cost, int& minCost)
  {
    if (times == 0)
    {
      if (cost < minCost)
      {
        minCost = cost;
      }
      return;
    }

    for (int i = 0; i < timbers.size(); i++)
    {
      for (int j = 1; j < timbers[i]; j++)
      {
        int left = j;
        int right = timbers[i] - j;

        std::vector<int> newTimbers = {};
        std::ranges::copy(timbers, std::back_inserter(newTimbers));
        auto it = newTimbers.erase(newTimbers.begin() + i);
        newTimbers.insert(it, {left, right});

        CutInternal(newTimbers, times - 1, cost + timbers[i], minCost);
      }
    }
  }
public:
  static int Cut(const int length, const int times)
  {
    int cost = INT_MAX;
    std::vector timbers = { length };

    CutInternal(timbers, times, 0, cost);

    return cost;
  }
};

int main(int argc, char* argv[])
{
  std::cout << TimberCutter::Cut(std::atoi(argv[1]), std::atoi(argv[2])) << std::endl;
}