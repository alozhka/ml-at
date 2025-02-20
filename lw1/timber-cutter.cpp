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

#include <cmath>
#include <iostream>
#include <list>
#include <ostream>

class TimberCutter {
public:
  static int Cut(const int length, int times) {
    int cost = 0;
    std::list timbers = {length};
    // [timbers, times, cost]

    while (times > 1) {
      int left, right;

      if (const int middle = timbers.front() / 2; times <= middle) {
        left = times;
        right = timbers.front() - times;
      } else {
        left = middle;
        right = timbers.front() - middle;
      }
      times--;
      cost += timbers.front();

      timbers.pop_front();
      if (right > 1) {
        timbers.push_front(right);
      }
      if (left > 1) {
        timbers.push_front(left);
      }
    }

    cost += timbers.front();
    return cost;
  }
};

int main(int argc, char *argv[]) {
  std::cout << TimberCutter::Cut(std::atoi(argv[1]), std::atoi(argv[2])) << std::endl;
}
