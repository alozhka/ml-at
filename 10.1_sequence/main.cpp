/*
10.1. Последовательность 1 (6)
В последовательности чисел a1, a2, a3, ... задан первый член, а остальные вычисляются по формуле ai = (ai - 1)2 mod M + 1.
Найти N-й член последовательности.
Ограничения: 1 ≤ M ≤ 10000,  2 ≤ N ≤ 10^18, 0 ≤ a1 ≤ M.
Ввод из файла INPUT.TXT. В первой строке находятся числа M, N и a1 , разделённые пробелом.
Вывод в файл OUTPUT.TXT. Вывести одно число - aN.
Примеры
Ввод 1      Ввод 2
10000 3 4   7777 2000000000 0
Вывод 1     Вывод 2
290         3834
Подсказка. Сколько разных чисел может быть в последовательности? Обязан ли в ней присутствовать цикл?
Обязательно ли цикл начинается с первого элемента?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using ull = unsigned long long;

ull FindInSequence(ull M, ull N, ull first)
{
	std::unordered_map<int, int> indexMap;
	std::vector<int> sequence;

	int current = first;
	int pos = 0;

	while (!indexMap.contains(current)) {
		indexMap[current] = pos;
		sequence.push_back(current);
		current = (1LL * current * current) % M + 1;
		pos++;
	}

	int prefixLength = indexMap[current];
	int cycleLength = sequence.size() - prefixLength;

	int result;
	if (N <= sequence.size()) {
		result = sequence[N - 1];
	} else {
		long long offset = (N - prefixLength - 1) % cycleLength;
		result = sequence[prefixLength + offset];
	}

	return result;
}

int main(const int _, const char * argv[]) {
	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	long long M;
	unsigned long long N;
	int a1;
	fin >> M >> N >> a1;

	ull result = FindInSequence(M, N, a1);

	fout << result << std::endl;

	return 0;
}