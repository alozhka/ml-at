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

// Функция проверки, содержит ли подмассив длины len прогрессию из m членов с разностью 13
bool hasProgression(vector<int>& arr, int len, int m, vector<int>& prog)
{
	for (int i = 0; i <= len - m; i++)
	{
		bool found = true;
		// Проверяем все возможные начала прогрессии
		for (int j = i + 1; j < len; j++)
		{
			int count = 2;
			int diff = arr[j] - arr[i];
			if (diff != 13)
				continue;

			int last = arr[j];
			for (int k = j + 1; k < len && count < m; k++)
			{
				if (arr[k] - last == 13)
				{
					count++;
					last = arr[k];
				}
			}

			if (count == m)
			{
				// Сохраняем найденную прогрессию
				prog.clear();
				prog.push_back(arr[i]);
				last = arr[i];
				for (int k = i + 1; k < len && prog.size() < m; k++)
				{
					if (arr[k] - last == 13)
					{
						prog.push_back(arr[k]);
						last = arr[k];
					}
				}
				return true;
			}
		}
	}
	return false;
}

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

	int k = 0;
	vector<int> progression;

	// Бинарный поиск по длине префикса
	int left = 0, right = args.maxAmount;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (!hasProgression(args.sequence, mid, args.progAmount, progression))
		{
			k = mid;
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}

	fout << k << endl;

	// Ищем первую прогрессию в минимальном префиксе, где она появляется
	if (k < args.maxAmount)
	{
		hasProgression(args.sequence, k + 1, args.progAmount, progression);
		for (int i = 0; i < progression.size(); i++)
		{
			fout << progression[i];
			if (i < progression.size() - 1)
				fout << " ";
		}
	}
	else
	{
		fout << "No";
	}

	fout << endl;
	fout.close();

	return 0;
}