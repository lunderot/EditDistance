#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void PrintDistanceMap(const vector<vector<int>> &distance, string word1, string word2)
{
	cout << "    ";
	for (unsigned int i = 0; i < word2.length(); i++)
	{
		cout << word2[i] << " ";
	}
	cout << endl;
	for (unsigned int i = 0; i < distance.size(); i++)
	{
		if (i == 0)
		{
			cout << " ";
		}
		else
		{
			cout << word1[i - 1];
		}
		cout << " ";
		for (unsigned int j = 0; j < distance[0].size(); j++)
		{
			cout << distance[i][j] << " ";
		}
		cout << endl;
	}
}

void InitDistanceMap(vector<vector<int>> &distance, string word1, string word2)
{
	int mapRowSize = word1.length() + 1;
	int mapCollumnSize = word2.length() + 1;

	distance.resize(mapRowSize, vector<int>(mapCollumnSize, 0));

	for (unsigned int i = 0; i < distance.size(); i++)
	{
		distance[i][0] = i;
	}
	for (unsigned int i = 0; i < distance[0].size(); i++)
	{
		distance[0][i] = i;
	}
}

void CalculateDistanceMap(	vector<vector<int>> &distance, string word1, string word2,
							int copyCost, int replaceCost, int deleteCost, int insertCost, int twiddleCost, int killCost)
{
	int mapRowSize = word1.length() + 1;
	int mapCollumnSize = word2.length() + 1;

	for (int i = 1; i < mapRowSize; i++)
	{
		for (int j = 1; j < mapCollumnSize; j++)
		{
			int count = 0;
			if (word1[i - 1] != word2[j - 1])
			{
				count = 1;
			}
			distance[i][j] = min(distance[i - 1][j], min(distance[i][j - 1], distance[i - 1][j - 1])) + count;
			cout << " distance[" << i << "][" << j << "] = " << distance[i][j] << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc == 9)
	{
		string word[2];
		word[0] = string(argv[1]);
		word[1] = string(argv[2]);

		int cost[6];
		for (int i = 0; i < 6; i++)
		{
			cost[i] = atoi(argv[i + 3]);
		}

		cout << "w1: " << word[0] << " len: " << word[0].length() << endl;
		cout << "w2: " << word[1] << " len: " << word[1].length() << endl;


		vector<vector<int>> distance;
		InitDistanceMap(distance, word[0], word[1]);
		PrintDistanceMap(distance, word[0], word[1]);

		CalculateDistanceMap(distance, word[0], word[1], cost[0], cost[1], cost[2], cost[3], cost[4], cost[5]);

		PrintDistanceMap(distance, word[0], word[1]);


	}
	else
	{
		cout << "Usage: " << argv[0] << " string1 string2 copyCost replaceCost deleteCost insertCost twiddleCost killCost" << endl;
	}
	cin.get();
	return 0;
}