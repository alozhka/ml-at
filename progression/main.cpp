/*
4.1. Прогрессия (6)
Король Камбузии с детства боится несчастливых арифметических прогрессий с разностью 13.
Однажды ему представили список расходов на нужды подданных, состоящий из N чисел.
Король потребовал оставить только такую начальную часть списка, в которой не скрывается несчастливая арифметическая прогрессия.
Либеральная общественность, считаясь с мнением короля, настаивает, тем не менее, на сохранении как можно большей части списка.
Найти максимальное значение K такое, что из первых K чисел списка невозможно выделить M чисел,
следующих в порядке их нахождения в списке и образующих последовательные члены несчастливой арифметической прогрессии.
Выдать члены первой обнаруженной несчастливой прогрессии.

Ввод из файла INPUT.TXT.
Первая строка содержит два целых положительных числа N и M, разделенных пробелом: N – количество чисел в списке,
а M – недопустимое число членов прогрессии. Вторая строка содержит список расходов в виде целых положительных чисел.
Ограничения: 2 ≤ N, M ≤ 5000, 1 ≤ Xi ≤ 65000, время 1 с.

Вывод в файл OUTPUT.TXT. В первой строке выводится единственное число K- максимальное количество начальных чисел списка,
не содержащих в качестве подсписка M последовательных членов несчастливой арифметической прогрессии.
Во второй строке выводятся через пробел члены первой обнаруженной несчастливой прогрессии. Если ее не обнаружено, вывести No.

Пример
Ввод
9 3
5 9 3 22 16 19 35 7 29
Вывод
6
9 22 35
Пояснение: из первых 7 чисел выделяются 3 члена несчастливой прогрессии 9, 22, 35,
а из первых 6 чисел можно выделить только 2 таких члена: 9, 22 либо 3, 16.
*/

#include <fstream>
#include <vector>

struct Args
{
	int maxAmount = 0, progAmount = 0;
	std::vector<int> sequence = {};
};

using namespace std;

void ParseArgs(Args& args, std::string_view filename)
{
	ifstream fin(filename);

	fin >> args.maxAmount >> args.progAmount;

	vector<int> arr(args.maxAmount);
	for (int i = 0; i < args.maxAmount; i++)
	{
		fin >> arr[i];
	}

	args.sequence = arr;
}

int main(const int _, const char* argv[])
{
	Args args;
	ofstream fout(argv[2]);
	ParseArgs(args, argv[1]);

	int N = args.maxAmount;
	int M = args.progAmount;
	const std::vector<int> expenses = args.sequence;

	vector<unordered_map<int, pair<int, int>>> dp(N);
	int K = N;
	vector<int> bad_progression;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int diff = expenses[i] - expenses[j];
			if (diff == 13) {
				dp[i][diff] = {dp[j][diff].first + 1, j};
				if (dp[i][diff].first >= M - 1 && i < K) {
					K = i;
					bad_progression.clear();
					int idx = i;
					vector<int> temp_progression;
					for (int k = 0; k < M; k++) {
						temp_progression.push_back(expenses[idx]);
						idx = dp[idx][diff].second;
					}
					reverse(temp_progression.begin(), temp_progression.end());
					if (bad_progression.empty() || temp_progression < bad_progression) {
						bad_progression = temp_progression;
					}
				}
			}
		}
	}

	fout << K << "\n";
	if (bad_progression.empty())
	{
		fout << "No\n";
	}
	else
	{
		for (int num : bad_progression)
		{
			fout << num << " ";
		}
		fout << "\n";
	}

	return 0;
}