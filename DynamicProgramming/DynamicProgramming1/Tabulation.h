#pragma once
#include <iostream>
#include <vector>

// Time Complexity : O(n)
// Space Complexity : O(n)
int64_t Fibonacci_Tab(const int n)
{
	//std::vector<int> table(n + 1);

	////base case
	//table[0] = 0;
	//table[1] = 1;

	//// tabulation
	//for (int i = 2; i <= n; i++)
	//{
	//	table[i] = table[i - 1] + table[i - 2];
	//}
	//return table[n];

	std::vector<int> table(n + 1, 0);
	table[1] = 1;
	for (int i = 0; i <= n; i++)
	{
		if (i + 1 <= n)
		{
			table[i + 1] += table[i];
		}
		if (i + 2 <= n)
		{
			table[i + 2] += table[i];
		}
	}
	return table[n];
}

// m x n 크기의 사각형이 주어졌을 때, 좌상단에서 출발하여 우하단으로 이동하는 모든 경우의 수를 구하시오 (재귀)
// 단, 오른쪽이나 아래쪽으로만 이동 가능
// Time Complexity : O(m *n)
// Space Complexity : O(m*n)
int64_t FindWays_Tab(const int m, const int n)
{
	//std::vector<std::vector<int>> table(m + 1, { std::vector<int>(n + 1,0) });

	//// base case
	//table[1][1] = 1;

	//for (int row = 1; row <= m; row++)
	//{
	//	for (int col = 1; col <= n; col++)
	//	{
	//		if (row == 1 && col == 1)
	//		{
	//			continue;
	//		}

	//		table[row][col] = table[row - 1][col] + table[row][col - 1];
	//	}
	//}

	//return table[m][n];


	std::vector<std::vector<int>> table(m + 1, std::vector<int>(n + 1, 0));
	table[1][1] = 1;

	for (int row = 0; row <= m; row++)
	{
		for (int col = 0; col <= n; col++)
		{
			if (row + 1 <= m)
			{
				table[row + 1][col] += table[row][col];
			}
			if (col + 1 <= n)
			{
				table[row][col + 1] += table[row][col];
			}
		}
	}
	return table[m][n];
}

// m : sum, n : numbers 크기
// Time Complexity : O(m x n) 
// Space Complexity : O(m)
bool CanAccum_Tab(const int sum, const std::vector<int> &numbers)
{
	std::vector<bool> table(sum + 1, false);

	table[0] = true;

	for (int i = 0; i <= sum; i++)
	{
		if (table[i])
		{
			for (auto e : numbers)
			{
				if (i + e <= sum)
				{
					table[i + e] = true;
				}

			}
		}
	}
	return table[sum];
}

// Time Complexity : O ( m * m * n)  = O(m^2 * n)
// Space Complexity : O(m * m) = O(m^2)
std::shared_ptr<std::vector<int>> HowAccum_Tab(const int sum, const std::vector<int> &numbers)
{
	std::vector< std::shared_ptr<std::vector<int>>> table(sum + 1, nullptr);

	table[0] = std::make_shared<std::vector<int>>(0);

	for (int i = 0; i <= sum; i++)
	{
		if (table[i] != nullptr)
		{
			for (auto e : numbers)
			{
				if (i + e <= sum)
				{
					table[i + e] = std::make_shared<std::vector<int>>(*table[i]);
					table[i + e]->push_back(e);
				}
			}
		}
	}

	return table[sum];
}

// Time Complexity : O (m*m*n) = O(m^2 * n)
// Space Complexity : O(m^2)
std::shared_ptr<std::vector<int>> OptimizeAccum_Tab(const int sum, const std::vector<int> &numbers)
{
	std::vector<std::shared_ptr<std::vector<int>>> table(sum + 1, nullptr);

	table[0] = std::make_shared<std::vector<int>>(0);

	for (int i = 0; i <= sum; i++)
	{
		if (table[i])
		{
			for (auto e : numbers)
			{
				if (i + e <= sum)
				{
					if (table[i + e] == nullptr || table[i + e]->size() - 1 > table[i]->size())
					{
						table[i + e] = std::make_shared<std::vector<int>>(*table[i]);
						table[i + e]->push_back(e);
					}
				}
			}
		}
	}
	return table[sum];
}
void Tabulation()
{
	std::cout << Fibonacci_Tab(5) << std::endl;
	std::cout << Fibonacci_Tab(40) << std::endl;

	std::cout << FindWays_Tab(2, 3) << std::endl;
	std::cout << FindWays_Tab(30, 30) << std::endl;
	
	std::cout << CanAccum_Tab(8, { 2,3,5 }) << std::endl;

	Print(HowAccum_Tab(8, { 2,3,5 }));
}
