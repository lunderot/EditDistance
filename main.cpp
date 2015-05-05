#include <iostream>
#include <vector>
#include <string>

using namespace std;

void PrintDistanceMap(const vector<vector<int>> &distance, string word1, string word2)
{
	cout << "    ";
	for (int i = 0; i < word1.length(); i++)
	{
		cout << word1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < distance.size(); i++)
	{
		if (i == 0)
		{
			cout << " ";
		}
		else
		{
			cout << word2[i - 1];
		}
		cout << " ";
		for (int j = 0; j < distance[0].size(); j++)
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

	for (int i = 0; i < distance.size(); i++)
	{
		distance[i][0] = i;
	}
	for (int i = 0; i < distance[0].size(); i++)
	{
		distance[0][i] = i;
	}
}

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		string word[2];
		word[0] = string(argv[1]);
		word[1] = string(argv[2]);

		cout << "w1: " << word[0] << " len: "<< word[0].length() << endl;
		cout << "w2: " << word[1] << " len: "<< word[1].length() << endl;
		
		vector<vector<int>> distance;
		

		PrintDistanceMap(distance, word[0], word[1]);

	}
	else
	{
		cout << "Usage: " << argv[0] << " string1 string2" << endl;
	}
	cin.get();
	return 0;
}