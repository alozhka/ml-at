/*
Ложкин Сергей, ПС-21
Среда: CMake

6.1. Счастливые билеты (8). Номера автобусных билетов состоят из 2N цифр, включая незначащие нули (1 ≤ N ≤ 500).
Минимальный возможный номер состоит из 2N нулей, а максимальный – из 2N девяток.
Студент Вася ездит в университет на автобусе и коллекционирует счастливые билеты,
в которых сумма первых N цифр совпадает с суммой последних N цифр. Как и всякий настоящий коллекционер,
Вася готов пойти на все для пополнения своей коллекции. Вместе с тем ему пока приходится учитывать свои финансовые возможности.
Каждый раз после приобретения билета Вася определяет, какое минимальное количество билетов нужно купить еще,
чтобы среди них обязательно оказался счастливый билет. Если у него оказывается достаточно денег,
он тут же покупает необходимое число билетов. Иногда он не успевает закончить расчеты,
проезжает свою остановку и опаздывает на занятия. Помогите Васе.

Ввод из файла INPUT.TXT. В первой строке находится число N. Во второй строке задан номер первого билета Васи из 2N цифр.

Вывод в файл OUTPUT.TXT. В единственной строке вывести минимальное число следующих билетов, необходимое для гарантированного получения счастливого билета.

Примеры
Ввод 1    Ввод 2    Ввод 3
2         2         2
3817      0839      0000
Вывод 1   Вывод 2   Вывод 3
12        5         0
*/
#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>
#include <string>

using ull = unsigned long long;
using namespace boost::multiprecision;

void readInput(std::string_view filename, int& N, std::string& ticket)
{
	std::ifstream fin(filename.data());
	fin >> N >> ticket;
	fin.close();
}

void writeOutput(std::string_view filename, const std::string& steps)
{
	std::ofstream fout(filename.data());
	fout << steps << "\n";
	fout.close();
}

ull CalculateSum(const cpp_int& num)
{
	std::string s = num.str();
	int sum = 0;
	for (char c : s)
	{
		sum += c - '0';
	}
	return sum;
}

cpp_int Pow(unsigned int n, unsigned int base)
{
	cpp_int result = n;
	for (int i = 0; i < base; ++i)
	{
		result *= 10;
	}
	return result;
}

void SplitTicket(int N, const std::string& ticket, cpp_int& s1, cpp_int& s2)
{
	for (int i = 0; i < N; ++i)
	{
		s1 *= 10;
		s1 += static_cast<short>(ticket[i] - '0');
	}
	for (int i = 0; i < N; ++i)
	{
		s2 *= 10;
		s2 += static_cast<short>(ticket[i + N] - '0');
	}
}

cpp_int round_up_to_next_digit(const cpp_int& x, short round)
{
	if (x <= 0)
		return 1;

	cpp_int base = 1;
	for (size_t i = 1; i < round; ++i)
		base *= 10;

	// Пример: x = 234, pos = 1, base = 1000 (234 + 100)/1000 = 3
	cpp_int result = ((x + base) / base) * base;

	return result;
}

cpp_int Solve(int N, const std::string& ticketStr)
{
	cpp_int s1 = 0;
	cpp_int s2 = 0;
	cpp_int steps = 0;
	SplitTicket(N, ticketStr, s1, s2);
	ull sum1 = CalculateSum(s1);
	ull sum2 = CalculateSum(s2);

	if (sum1 == sum2)
	{
		return 0;
	}

	while (sum1 != sum2)
	{
		if (sum1 < sum2)
		{
			ull tempSum = 0, pos = 0;
			for (; tempSum < sum1; ++pos)
			{
				tempSum += static_cast<ull>(s2.str()[pos] - '0');
			}
			--pos;
			cpp_int oldS2 = s2;
			s2 = round_up_to_next_digit(s2, N - pos);
			steps += s2 - oldS2;
			if (s2.str(0, 0).length() > N)
			{
				++s1;
				s2 = 0;
			}
		}
		else
		{
			++s2;
			++steps;
		}

		sum1 = CalculateSum(s1);
		sum2 = CalculateSum(s2);
	}

	return steps;
}

int main(const int _, const char* argv[])
{
	int N;
	std::string ticket;
	readInput(argv[1], N, ticket);
	cpp_int answer = Solve(N, ticket);
	writeOutput(argv[2], answer.str());
	return 0;
}
