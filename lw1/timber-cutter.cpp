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

#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>

class TimberCutter {
public:
  static int Cut(const int length, int times) {
    int cost = 0;
    std::vector timbers = {length};

    while (times > 1) {
      int left, right;
      const int timber = timbers.back(), middle = timber / 2;

      if (times <= middle) {
        left = times;
        right = timber - times;
      } else {
        left = middle;
        right = timber - middle;
      }
      times--;
      cost += timber;

      timbers.pop_back();
      if (right > 1) {
        timbers.push_back(right);
      }
      if (left > 1) {
        timbers.push_back(left);
      }
    }

    cost += timbers.back();
    return cost;
  }
};

int main(int _, char *argv[]) {
  int length, times;
  std::ifstream in(argv[1]);
  in >> length;
  in >> times;

  std::cout << TimberCutter::Cut(length, times) << std::endl;
}
