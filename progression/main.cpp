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

struct Progression
{
	int maxK = 0;
	std::vector<int> progression = {};
};

void ParseArgs(Args& args, std::string_view filename)
{
	std::ifstream fin(filename);

	fin >> args.maxAmount >> args.progAmount;

	std::vector<int> arr(args.maxAmount);
	for (int i = 0; i < args.maxAmount; i++)
	{
		fin >> arr[i];
	}

	args.sequence = arr;
}

Progression FindSafePrefix(const std::vector<int>& arr, const int n, const int m)
{
	std::vector dp(n, 1);
	std::vector prev(n, -1);

	int maxK = 0;
	std::vector<int> progression;
	bool found = false;

	for (int i = 0; i < n; i++)
	{
		if (!found)
		{
			for (int j = 0; j < i; j++)
			{
				if (arr[i] - arr[j] == 13)
				{
					const int newLen = dp[j] + 1;
					if (newLen > dp[i])
					{
						dp[i] = newLen;
						prev[i] = j;

						if (newLen == m)
						{
							int curr = i;
							while (curr != -1 && progression.size() < m)
							{
								progression.push_back(arr[curr]);
								curr = prev[curr];
							}
							std::ranges::reverse(progression);
							maxK = i;
							found = true;
							break;
						}
					}
				}
			}
			if (!found && dp[i] < m)
			{
				maxK = i + 1;
			}
		}
	}

	return { maxK, progression };
}

void PrintProgression(const std::string& filename, const Progression& result)
{
	std::ofstream out(filename);

	out << result.maxK << std::endl;

	if (result.progression.empty())
	{
		out << "No" << std::endl;
	}
	else
	{
		for (int i = 0; i < result.progression.size(); i++)
		{
			out << result.progression[i];
			if (i < result.progression.size() - 1)
				out << " ";
		}
		out << std::endl;
	}
}

int main(const int _, const char* argv[])
{
	Args args;
	ParseArgs(args, argv[1]);

	const Progression result = FindSafePrefix(args.sequence, args.maxAmount, args.progAmount);

	PrintProgression(argv[2], result);

	return 0;
}