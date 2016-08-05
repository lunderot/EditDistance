#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

#include "Operation.h"

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

void PrintOperationMap(const vector<vector<Operation>>& operation, string word1, string word2)
{
	cout << "     ";
	for (unsigned int i = 0; i < word2.length(); i++)
	{
		cout << word2[i] << "  ";
	}
	cout << endl;
	for (unsigned int i = 0; i < operation.size(); i++)
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
		for (unsigned int j = 0; j < operation[0].size(); j++)
		{
			cout << operation[i][j] << " ";
		}
		cout << endl;
	}
}

void CalculateOperations(const vector<vector<Operation>>& operation, const vector<vector<int>> &distance, vector<Operation>& finalOperations, int i, int j)
{
	int nexti = -1;
	int nextj = -1;
	int nextdistance = std::numeric_limits<int>::max();
	if (i <= 0 || j <= 0)
	{
		return;
	}
	finalOperations.push_back(operation[i][j]);
	if (distance[i - 1][j - 1] < nextdistance)
	{
		nextdistance = distance[i - 1][j - 1];
		nexti = i - 1;
		nextj = j - 1;
	}
	if (distance[i][j - 1] < nextdistance)
	{
		nextdistance = distance[i][j - 1];
		nexti = i;
		nextj = j - 1;
	}
	if (distance[i - 1][j] < nextdistance)
	{
		nextdistance = distance[i - 1][j];
		nexti = i - 1;
		nextj = j;
	}
	CalculateOperations(operation, distance, finalOperations, nexti, nextj);
}

void CalculateOperations(const size_t wordSize, const vector<vector<Operation>>& operation, const vector<vector<int>> &distance, vector<Operation>& finalOperations)
{
	int isize = operation.size() - 1;
	int jsize = operation[0].size() - 1;
	CalculateOperations(operation, distance, finalOperations, isize, jsize);

	reverse(finalOperations.begin(), finalOperations.end());

	//Check for twiddle operations and remove the operation before since twiddle operates on two letters
	for (auto i = finalOperations.begin(); i != finalOperations.end(); )
	{
		if (next(i) != finalOperations.end() && next(i)->GetType() == Operation::Twiddle)
		{
			i = finalOperations.erase(i);
		}
		else
		{
			++i;
		}
	}
	//Check if it's possible to replace delete operations with a kill operation
	int deleteCounter = 0;
	for (auto i = finalOperations.rbegin(); i != finalOperations.rend(); i++)
	{
		if (i->GetType() == Operation::Delete)
		{
			deleteCounter++;
		}
		else
		{
			break;
		}
	}
	//Remove the delete operations at the end
	finalOperations.erase(finalOperations.end() - deleteCounter, finalOperations.end());
	//Add the kill operation to the end if needed
	if (deleteCounter > 0)
	{
		finalOperations.push_back(Operation(Operation::Kill, (int)wordSize));
	}
	
}

int GetDistance(const vector<vector<int>>& distance, string word1, string word2)
{
	return distance.back().back();
}

void InitMap(vector<vector<int>>& distance, vector<vector<Operation>>& operation, string word1, string word2, int deleteCost, int insertCost)
{
	int mapRowSize = word1.length() + 1;
	int mapColumnSize = word2.length() + 1;

	distance.resize(mapRowSize, vector<int>(mapColumnSize, numeric_limits<int>::max()));
	operation.resize(mapRowSize, vector<Operation>(mapColumnSize));

	for (unsigned int i = 0; i < distance.size(); i++)
	{
		distance[i][0] = i * deleteCost;
		operation[i][0] = Operation(Operation::Delete);
	}
	for (unsigned int i = 0; i < distance[0].size(); i++)
	{
		distance[0][i] = i * insertCost;
		operation[0][i] = Operation(Operation::Insert, word2[i]);
	}
}

void CalculateDistanceMap(vector<vector<int>>& distance, vector<vector<Operation>>& operation, string word1, string word2,
	int copyCost, int replaceCost, int deleteCost, int insertCost, int twiddleCost, int killCost)
{
	int mapRowSize = word1.length() + 1;
	int mapColumnSize = word2.length() + 1;

	for (int i = 1; i < mapRowSize; i++)
	{
		for (int j = 1; j < mapColumnSize; j++)
		{
			//Copy
			if (word1[i - 1] == word2[j - 1])
			{
				distance[i][j] = distance[i - 1][j - 1] + copyCost;
				operation[i][j] = Operation(Operation::Copy);
			}
			//Replace
			if (word1[i - 1] != word2[j - 1] && distance[i - 1][j - 1] + replaceCost < distance[i][j])
			{
				distance[i][j] = distance[i - 1][j - 1] + replaceCost;
				operation[i][j] = Operation(Operation::Replace, word2[j - 1]);
			}
			//Twiddle
			if (i >= 2 && j >= 2 &&
				word1[i - 1] == word2[j - 2] &&
				word1[i - 2] == word2[j - 1] &&
				distance[i - 2][j - 2] + twiddleCost < distance[i][j]
				)
			{
				distance[i][j] = distance[i - 2][j - 2] + twiddleCost;
				operation[i][j] = Operation(Operation::Twiddle);
			}
			//Delete
			if (distance[i - 1][j] + deleteCost < distance[i][j])
			{
				distance[i][j] = distance[i - 1][j] + deleteCost;
				operation[i][j] = Operation(Operation::Delete);
			}
			//Insert
			if (distance[i][j - 1] + insertCost < distance[i][j])
			{
				distance[i][j] = distance[i][j - 1] + insertCost;
				operation[i][j] = Operation(Operation::Insert, word2[j - 1]);
			}
		}
	}
}

void PrintFinalOperations(vector<Operation>& finalOperations)
{
	for (auto i = finalOperations.begin(); i != finalOperations.end(); i++)
	{
		cout << *i << " ";
	}
}

int CalculateFinalCost(const vector<Operation>& finalOperations,
	int copyCost, int replaceCost, int deleteCost, int insertCost, int twiddleCost, int killCost)
{
	int finalCost = 0;
	for (auto i = finalOperations.begin(); i != finalOperations.end(); i++)
	{
		switch (i->GetType())
		{
		case Operation::Copy:
			finalCost += copyCost;
			break;
		case Operation::Replace:
			finalCost += replaceCost;
			break;
		case Operation::Delete:
			finalCost += deleteCost;
			break;
		case Operation::Insert:
			finalCost += insertCost;
			break;
		case Operation::Twiddle:
			finalCost += twiddleCost;
			break;
		case Operation::Kill:
			finalCost += killCost;
			break;
		default:
			break;
		}
	}
	return finalCost;
}

int main(int argc, char* argv[])
{
	if (argc == 9)
	{
		Operation::SetPrintType(Operation::PrintType::Short);

		string word[2];
		word[0] = string(argv[1]);
		word[1] = string(argv[2]);

		int cost[6];
		for (int i = 0; i < 6; i++)
		{
			cost[i] = atoi(argv[i + 3]);
		}

		vector<vector<int>> distance;
		vector<vector<Operation>> operation;

		InitMap(distance, operation, word[0], word[1], cost[2], cost[3]);

		CalculateDistanceMap(distance, operation, word[0], word[1], cost[0], cost[1], cost[2], cost[3], cost[4], cost[5]);

		cout << "Distance map:" << endl;
		PrintDistanceMap(distance, word[0], word[1]);

		cout << "Operation map:" << endl;
		PrintOperationMap(operation, word[0], word[1]);

		vector<Operation> finalOperations;
		CalculateOperations(word[1].length(), operation, distance, finalOperations);

		cout << endl << endl << "Final opertions: " << endl << word[0]  << " to " << word[1] << endl;
		Operation::SetPrintType(Operation::PrintType::Long);
		PrintFinalOperations(finalOperations);

		//Final cost
		int finalCost = CalculateFinalCost(finalOperations, cost[0], cost[1], cost[2], cost[3], cost[4], cost[5]);
		cout << endl << endl << "Final cost: " << finalCost << endl;
	}
	else
	{
		cout << "Usage: " << argv[0] << " string1 string2 copyCost replaceCost deleteCost insertCost twiddleCost killCost" << endl;
	}
	cin.get();
	return 0;
}