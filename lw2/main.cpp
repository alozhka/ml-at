/*

Ложкин Сергей, ПС-21
Среда: C++, CMake

1.9. Дамба (9)
В рыбохозяйстве "Рыбнастол" принято решение о разведении карасей и щук.

К сожалению, эти рыбы не могут быть вместе в одном водоеме, так как щуки предпочитают питаться исключительно карасями.
Планируется каждое из k озер разделить дамбой на две не сообщающиеся друг с другом части.
На карте каждое i-е озеро представлено в определенном масштабе прямоугольным  участком  mi × ni единиц,
разбитым на единичные квадраты. Отдельный квадрат целиком занят водой или сушей. Множество водных квадратов является связным.
Это означает, что из любого водного квадрата озера можно попасть в любой другой водный квадрат,
последовательно переходя по водным квадратам через их общую сторону.
Такие последовательности связанных квадратов будем называть путями.

Дамба имеет вид непрерывной ломаной, проходящей по сторонам квадратов.
Два водных квадрата, общая сторона которых принадлежит ломаной, становятся не сообщающимися напрямую друг с другом.
Требуется для каждого озера определить минимальную по количеству сторон длину дамбы,
разделяющей озеро на две не сообщающиеся между собой связные части.
Чтобы обеспечить доступ рыбаков к воде, каждая из двух полученных частей озера должна сообщаться с берегом.
Иными словами, каждая часть должна содержать водный квадрат,
который либо сам находится на границе исходного прямоугольного участка, либо имеет общую сторону с квадратом суши,
связанным с границей путем из квадратов суши.

Ввод.
В первой строке содержится число k (1 ≤ k ≤ 10).
В следующих строках следуют k блоков данных. Каждый блок описывает одно озеро.
В первой строке блока содержатся числа mi и ni, разделенные пробелом.
В следующих mi строках находится матрица, представляющая озеро, по ni символов в строке.
Символ '.' обозначает квадрат суши, а символ '#' – квадрат воды.
Гарантируется наличие не менее двух водных квадратов.
Общая площадь озер s = m1 × n1 + m2 × n2 + … + mk × nk не должна превосходить 106.

Вывод.
В единственной строке должны выводиться через пробел k значений, определяющих минимальные длины дамб. В
результате каждое озеро должно быть разделено на две части так,
что водные клетки из разных частей не могут иметь общей стороны, не принадлежащей дамбе.
Тем не менее касание этих клеток углами допускается.
Каждая часть должна быть связана с берегом так, как это определялось выше.

Примеры
Ввод
2
3 6
......
.####.
.####.
3 5
##.##
#####
##.##
Вывод
2 1

 */

#include <fstream>
#include <iostream>
#include <vector>

using Lake = std::vector<std::string>;
using Mask = std::vector<std::vector<bool>>;

namespace Directions
{
constexpr std::array<std::array<int, 2>, 4> FourDirections = {
	{ { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } }
};
constexpr std::array<std::array<int, 2>, 8> EightDirections = {
	{ { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } }
};
} // namespace Directions

Lake InitLake(std::istream& in, const size_t rows, const size_t columns)
{
	Lake l;

	l.emplace_back(columns + 2, '.');

	for (size_t i = 0; i < rows; i++)
	{
		std::string row;
		in >> row;
		l.push_back('.' + row.substr(0, columns) + '.');
	}

	l.emplace_back(columns + 2, '.');

	return l;
}

Mask MaskLakeInFourDirections(const Lake& lake, const size_t rows, const size_t columns)
{
	Mask mask;
	mask.assign(rows, std::vector(columns, false));
	std::queue<std::pair<int, int>> queue;
	queue.emplace(0, 0);

	while (!queue.empty())
	{
		const auto [row, col] = queue.front();
		queue.pop();

		for (size_t d = 0; d < 4; d++)
		{
			int newRow = row + Directions::FourDirections[d][0];
			int newCol = col + Directions::FourDirections[d][1];

			if (0 <= newRow && newRow < rows && 0 <= newCol && newCol < columns)
			{
				if (lake[newRow][newCol] == '.' && !mask[newRow][newCol])
				{
					mask[newRow][newCol] = true;
					queue.emplace(newRow, newCol);
				}
			}
		}
	}

	return mask;
}

Mask MaskLakeInEightDirections(const Lake& lake, const size_t rows, const size_t columns)
{
	Mask mask;
	mask.assign(rows, std::vector(columns, false));
	std::queue<std::pair<int, int>> queue;
	queue.emplace(0, 0);

	while (!queue.empty())
	{
		auto [row, col] = queue.front();
		queue.pop();

		for (size_t d = 0; d < 8; d++)
		{
			int newRow = row + Directions::EightDirections[d][0];
			int newCol = col + Directions::EightDirections[d][1];

			if (0 <= newRow && newRow < rows && 0 <= newCol && newCol < columns)
			{
				if (lake[newRow][newCol] == '.' && !mask[newRow][newCol])
				{
					mask[newRow][newCol] = true;
					queue.emplace(newRow, newCol);
				}
			}
		}
	}

	return mask;
}

size_t FindMinDamByMasks(const Lake& lake, const Mask& m4, const Mask& m8)
{
	for (size_t row = 0; row < m4.size(); row++)
	{
		for (size_t col = 0; col < m4.size(); col++)
		{
			if (lake[row][col] == '#' && lake[row][col + 1] == '#')
			{
				if ((m4[row - 1][col]		&& m8[row + 1][col]		|| m8[row - 1][col]		&& m4[row + 1][col])		||
					(m4[row - 1][col]		&& m8[row + 1][col + 1] || m8[row - 1][col]		&& m4[row + 1][col + 1])	||
					(m4[row - 1][col + 1]	&& m8[row + 1][col + 1] || m8[row - 1][col + 1] && m4[row + 1][col + 1])	||
					(m4[row - 1][col + 1]	&& m8[row + 1][col]		|| m8[row - 1][col + 1] && m4[row + 1][col])
				)
				{
					return 1;
				}
			}

			if (lake[row][col] == '#' && lake[row + 1][col] == '#')
			{
				if ((m4[row][col - 1]		&& m8[row][col + 1]		|| m8[row][col - 1]		&& m4[row][col + 1])		||
					(m4[row][col - 1]		&& m8[row + 1][col + 1] || m8[row][col - 1]		&& m4[row + 1][col + 1])	||
					(m4[row + 1][col - 1]	&& m8[row + 1][col + 1] || m8[row + 1][col - 1] && m4[row + 1][col + 1])	||
					(m4[row + 1][col - 1]	&& m8[row][col + 1]		|| m8[row + 1][col - 1] && m4[row][col + 1])
				)
				{
					return 1;
				}
			}
		}
	}

	return 2;
}

int main(const int _, const char* argv[])
{
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);

	size_t lakesCount;
	in >> lakesCount;
	std::vector<size_t> results;

	for (size_t i = 0; i < lakesCount; i++)
	{
		size_t rows, columns;
		in >> rows >> columns;
		Lake l = InitLake(in, rows, columns);
		rows += 2;
		columns += 2;
		Mask m4 = MaskLakeInFourDirections(l, rows, columns);
		Mask m8 = MaskLakeInEightDirections(l, rows, columns);

		size_t minDam = FindMinDamByMasks(l, m4, m8);
		results.push_back(minDam);
	}

	for (const size_t d : results)
	{
		out << d << ' ';
	}

	out << std::endl;
}