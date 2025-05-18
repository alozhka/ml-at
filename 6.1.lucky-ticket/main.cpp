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
#include <fstream>
#include <span>
#include <string>
#include <vector>

using ull = unsigned long long;

void readInput(std::string_view filename, int& N, std::string& ticket)
{
	std::ifstream fin(filename.data());
	fin >> N >> ticket;
	fin.close();
}

void writeOutput(std::string_view filename, ull steps)
{
	std::ofstream fout(filename.data());
	fout << steps << "\n";
	fout.close();
}

// Увеличиваем номер билета на 1
void incrementTicket(std::vector<short>& digits)
{
	int n = digits.size();
	int carry = 1;
	for (int i = n - 1; i >= 0 && carry; --i)
	{
		int sum = digits[i] + carry;
		digits[i] = sum % 10;
		carry = sum / 10;
	}
}

ull digitsToNumber(const std::vector<short>& digits)
{
	ull res = 0;
	for (const int d : digits)
	{
		res *= 10;
		res += d;
	}
	return res;
}

void fillVector(std::vector<short>& v, short n)
{
	for (short& i : v)
	{
		i = n;
	}
}

ull CalculateSum(const std::vector<short>& v)
{
	ull res = 0;
	std::ranges::for_each(v, [&res](short digit) { res += digit; });
	return res;
}

ull solve(int N, const std::string& ticketStr)
{
	std::vector<short> digits(2 * N);
	std::vector<short> s1(N);
	std::vector<short> s2(N);
	for (int i = 0; i < 2 * N; ++i)
	{
		digits[i] = static_cast<short>(ticketStr[i] - '0');
	}
	for (int i = 0; i < N; ++i)
	{
		s1[i] = digits[i];
	}
	for (int i = 0; i <= N; ++i)
	{
		s2[i] = digits[i + N];
	}

	ull steps = 0;
	ull sum1 = CalculateSum(s1);
	ull sum2 = CalculateSum(s2);

	if (sum1 == sum2)
	{
		return 0;
	}

	while (sum1 != sum2)
	{
		if (sum1 < s2.front())
		{
			incrementTicket(s1);
			steps += std::pow(10, N) - digitsToNumber(s2);
			fillVector(s2, 0);
			continue;
		}

		incrementTicket(s2);
		++steps;

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
	ull answer = solve(N, ticket);
	writeOutput(argv[2], answer);
	return 0;
}
