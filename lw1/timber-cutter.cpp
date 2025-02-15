#include <vector>

class TimberCutter
{
	static void CutInternal(std::vector<int>& timbers, int times, int cost, int& minCost)
	{
		if (times == 0)
		{
			if (cost < minCost)
			{
				minCost = cost;
			}
			return;
		}

		for (int i = 0; i < timbers.size(); i++)
		{
			for (int j = 1; j < timbers[i]; j++)
			{
				int left = j;
				int right = timbers[i] - j;
				cost += timbers[i];

				std::vector<int> newTimbers = timbers;
				newTimbers.erase(timbers.begin() + i);
				newTimbers.push_back(left);
				newTimbers.push_back(right);

				CutInternal(newTimbers, times - 1, cost, minCost);
			}
		}
	}
public:
	static int Cut(int length, int times)
	{
		int cost = INT_MAX;
		std::vector<int> timbers = { length };

		CutInternal(timbers, times, 0, cost);

		return cost;
	}
};
