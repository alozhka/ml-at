/*

Ложкин Сергей, ПС-21
Среда: CMake

3.3. Распил бруса (6)
На пилораму привезли брус длиной L метров. Известны места, в которых необходимо сделать распилы.
Стоимость одного распила равна длине распиливаемого бруса.
Различный порядок распилов приводит к различным итоговым ценам. Например, брус длиной 10 метров,
который нужно распилить на расстоянии 2, 4 и 7 метров можно пилить разными способами.
Можно распилить сначала на отметке 2, потом 4 и потом 7. Стоимость будет 10+8+6=24.
А если сначала распилить на отметке 4, потом 2 и затем 7, то стоимость составит 10+4+6=20.
Требуется написать программу, которая определяла бы минимальную стоимость распила.

Ввод из файла INPUT.TXT.
В первой строке содержатся через пробел натуральные числа L и N (1 ≤ L ≤ 500, N < L) – длина бруса и число разрезов.
Вторая строка содержит N натуральных чисел Ci (0 < Ci < L) через пробел,
задающих в строго возрастающем порядке места, в которых нужно сделать распилы.
Вывод в файл OUTPUT.TXT. В единственной строке вывести минимальную стоимость распилов.

Примеры
Ввод 1		Ввод 2
10 2		10 4
2 7			4 5 7 8

Вывод 1		Вывод 2
17			22
 */

#include <fstream>
#include <iostream>
#include <span>

std::vector<size_t> ParseCuts(const std::string& filename)
{
	std::ifstream in(filename);
	size_t l, n;

	in >> l >> n;
	std::vector<size_t> cuts(n + 2);
	cuts[0] = 0;

	for (size_t i = 1; i <= n; i++)
	{
		in >> cuts[i];
	}

	cuts[n + 1] = l;

	return cuts;
}

size_t CutTimber(const std::span<size_t>& cuts)
{
	const size_t lastCutIndex = cuts.size() - 1;
	if (lastCutIndex == 1)
	{
		return 0;
	}

	const size_t length = cuts[lastCutIndex] - cuts[0];
	size_t min = std::numeric_limits<size_t>::max();
	for (int i = 1; i < lastCutIndex; i++)
	{
		const size_t l = CutTimber(cuts.first(i + 1));
		const size_t r = CutTimber(cuts.last(lastCutIndex - i + 1));
		const size_t cost = l + r;

		if (min > cost)
		{
			min = cost;
		}
	}

	return length + min;
}

int main(const int _, const char* argv[])
{
	std::ofstream out(argv[2]);
	std::vector<size_t> cuts = ParseCuts(argv[1]);

	const size_t sum = CutTimber(cuts);
	out << sum << std::endl;
	return 0;
}