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
#include <string>

using ull = unsigned long long;

void ReadTicket(std::string_view filename, int& N, std::string& ticket)
{
	std::ifstream in(filename.data());
	in >> N >> ticket;
}

void PrintAnswer(std::string_view filename, ull answer)
{
	std::ofstream out(filename.data());
	out << answer << std::endl;
}

bool IsLucky(const std::string& ticket, int N)
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

ull FindMinLengthToTicket(int N, const std::string& startTicket)
{
	ull current = 0;
	for (char c : startTicket)
	{
		current = current * 10 + (c - '0');
	}

	int totalLength = 2 * N;
	ull steps = 0;

	for (; true; current++, steps++)
	{
		std::string ticket = numberToTicket(current, totalLength);
		if (IsLucky(ticket, N))
		{
			break;
		}
	}

	return steps;
}

int main(const int _, const char* argv[])
{
	int N;
	std::string ticket;
	ReadTicket(argv[1], N, ticket);
	const ull answer = FindMinLengthToTicket(N, ticket);
	PrintAnswer(argv[2], answer);
	return 0;
}
