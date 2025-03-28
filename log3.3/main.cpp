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
#include <limits>
#include <vector>

size_t CutCost(const size_t L, const std::vector<size_t>& cut_positions)
{
	const size_t cutsAmount = cut_positions.size();
	std::vector<size_t> cuts = { 0 };
	cuts.insert(cuts.end(), cut_positions.begin(), cut_positions.end());
	cuts.push_back(L);

	std::vector cutCost(cutsAmount + 2, std::vector<size_t>(cutsAmount + 2, 0));

	for (size_t length = 2; length <= cutsAmount + 1; length++)
	{
		for (size_t i = 0; i + length <= cutsAmount + 1; i++)
		{
			const size_t j = i + length;
			cutCost[i][j] = std::numeric_limits<size_t>::max();

			for (size_t k = i + 1; k < j; ++k)
			{
				const size_t totalCost = cutCost[i][k] + cutCost[k][j] + cuts[j] - cuts[i];
				cutCost[i][j] = std::min(cutCost[i][j], totalCost);
			}
		}
	}

	return cutCost[0][cutsAmount + 1];
}

int main(int _, char* argv[])
{
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);

	size_t L, N;
	in >> L >> N;

	std::vector<size_t> cuts(N);
	for (size_t& cut : cuts)
	{
		in >> cut;
	}

	out << CutCost(L, cuts) << std::endl;
	return 0;
}
