/*
Ложкин Сергей, ПС-21

6.1. Счастливые билеты (8). Номера автобусных билетов состоят из 2N цифр, включая незначащие нули (1 ≤ N ≤ 500). Минимальный возможный номер состоит из 2N нулей, а максимальный – из 2N девяток. Студент Вася ездит в университет на автобусе и коллекционирует счастливые билеты, в которых сумма первых N цифр совпадает с суммой последних N цифр. Как и всякий настоящий коллекционер, Вася готов пойти на все для пополнения своей коллекции. Вместе с тем ему пока приходится учитывать свои финансовые возможности.
Каждый раз после приобретения билета Вася определяет, какое минимальное количество билетов нужно купить еще, чтобы среди них обязательно оказался счастливый билет. Если у него оказывается достаточно денег, он тут же покупает необходимое число билетов. Иногда он не успевает закончить расчеты, проезжает свою остановку и опаздывает на занятия. Помогите Васе.
Ввод из файла INPUT.TXT. В первой строке находится число N. Во второй строке задан номер первого билета Васи из 2N цифр.
Вывод в файл OUTPUT.TXT. В единственной строке вывести минимальное число следующих билетов, необходимое для гарантированного получения счастливого билета.
Примеры
Ввод 1    Ввод 2    Ввод 3
2         2         2
3817      0839      0000
Вывод 1   Вывод 2   Вывод 3
12        5         0
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using ull = unsigned long long;

// Считываем данные
void readInput(std::string_view filename, int& N, std::string& ticket)
{
	std::ifstream fin(filename.data());
	fin >> N >> ticket;
	fin.close();
}

// Записываем данные
void writeOutput(std::string_view filename, ull answer)
{
	std::ofstream fout(filename.data());
	fout << answer << "\n";
	fout.close();
}

// Проверяем, счастливый ли билет
bool isLucky(const std::string& ticket, int N)
{
	int left_sum = 0, right_sum = 0;
	for (int i = 0; i < N; i++)
	{
		left_sum += ticket[i] - '0';
	}
	for (int i = N; i < 2 * N; i++)
	{
		right_sum += ticket[i] - '0';
	}
	return left_sum == right_sum;
}

// Преобразуем число в строку длины 2N с ведущими нулями
std::string numberToTicket(ull number, int totalLength)
{
	std::string result(totalLength, '0');
	for (int i = totalLength - 1; i >= 0; i--)
	{
		result[i] = number % 10 + '0';
		number /= 10;
	}
	return result;
}

ull solve(int N, const std::string& startTicket)
{
	ull current = 0;
	for (char c : startTicket)
	{
		current = current * 10 + (c - '0');
	}

	int totalLength = 2 * N;
	ull steps = 0;

	while (true)
	{
		std::string ticket = numberToTicket(current, totalLength);
		if (isLucky(ticket, N))
		{
			break;
		}
		++current;
		++steps;
	}

	return steps;
}

int main(const int _, const char* argv[])
{
	int N;
	std::string ticket;
	readInput(argv[1], N, ticket);
	ull answer = solve(N, ticket);
	writeOutput(argv[2], answer);
	return 0;
}
