/*
Ложкин Сергей, ПС-21
Среда: CMake

14.10. Распил бруса 2 (10)
На пилораму привезли брус длиной L метров. Требуется сделать N распилов.
Распилы делят брус на части, длина которых выражается натуральными числами. Стоимость одного распила равна длине
распиливаемого бруса. Определить минимальную стоимость распила. Ввод. В первой строке содержатся через пробел
натуральные числа L (2 ≤ L ≤ 106) и N (N < L) – длина бруса и число распилов. Вывод. В единственной строке вывести
минимальную стоимость распилов.

Примеры
Ввод 1         Ввод 2
100 3          10 4
Вывод 1        Вывод 2
105            18
*/

#include <climits>
#include <cmath>
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

      if (times == 1) {
        const int minLog = *std::min_element(timbers.begin(), timbers.end());
        minCost = std::min(minLog + cost, minCost);
        continue;
      }

      for (int i = 0; i < timbers.size(); i++) {
          int left, right, middle = std::floor(timbers[i] / 2);
          if (times <= middle) {
            left = times;
            right = timbers[i] - times;
          } else {
            left = middle;
            right = timbers[i] - middle;
          }
          int newCost = cost + timbers[i];

          if (newCost >= minCost) {
            continue;
          }

          std::vector newTimbers{timbers};
          newTimbers.erase(newTimbers.begin() + i);
          if (left > 1) {
            newTimbers.push_back(left);
          }
          if (right > 1) {
            newTimbers.push_back(right);
          }

          dataStack.emplace(newTimbers, times - 1, newCost);
      }
    }

    return minCost;
  }
};

int main(int argc, char *argv[]) {
  std::cout << TimberCutter::Cut(std::atoi(argv[1]), std::atoi(argv[2])) << std::endl;
}
