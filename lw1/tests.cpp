#define CATCH_CONFIG_MAIN
#include "pch.h"
#include "timber-cutter.cpp"


TEST_CASE("Cuts a timber with minimal cost", "[positive]")
{
	std::vector<std::tuple<int, int, int>> testData =
	{
		{10, 4, 18},
		{100, 3, 105}
	};

	for (auto& data : testData)
	{
		int length = std::get<0>(data);
		int timesCut = std::get<1>(data);
		int result = std::get<2>(data);

		REQUIRE(TimberCutter::Cut(length , timesCut) == result);
	}
}
