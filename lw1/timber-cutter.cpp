/*
Ложкин Сергей, ПС-21
Среда: CMake

14.10. Распил бруса 2 (10)
На пилораму привезли брус длиной L метров. Требуется сделать N распилов.
Распилы делят брус на части, длина которых выражается натуральными числами. Стоимость одного распила равна длине
распиливаемого бруса. Определить минимальную стоимость распила. Ввод. В первой строке содержатся через пробел
натуральные числа L (2 ≤ L ≤ 10^6) и N (N < L) – длина бруса и число распилов. Вывод. В единственной строке вывести
минимальную стоимость распилов.

Примеры
Ввод 1         Ввод 2
100 3          10 4
Вывод 1        Вывод 2
105            18
*/

#include <fstream>
#include <ostream>
#include <queue>
#include <vector>

class TimberCutter
{
public:
	static size_t Cut(const int length, const int times)
	{
		size_t cost = 0;
		std::priority_queue<int, std::vector<int>, std::greater<>> timbers;
		for (int i = 0; i < times; i++)
		{
			timbers.push(1);
		}
		timbers.push(length - times);

		while (timbers.size() > 1)
		{
			const int left = timbers.top();
			timbers.pop();
			const int right = timbers.top();
			timbers.pop();

			int connectedTimber = left + right;
			cost += connectedTimber;
			timbers.push(connectedTimber);
		}

		return cost;
	}
};

int main(int _, char* argv[])
{
	int length, times;
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);
	in >> length;
	in >> times;

	out << TimberCutter::Cut(length, times) << std::endl;
	out.close();

	return 0;
}
