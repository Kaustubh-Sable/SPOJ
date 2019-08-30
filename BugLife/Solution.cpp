// https://www.spoj.com/problems/BUGLIFE/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool checkBugInteraction(vector<vector<int>> adjList, int nBugs);

int main()
{
	int scenarios, nBugs, bug1, bug2, i, j;
	long nInteractions;
	cin >> scenarios;
	while (scenarios--)
	{
		bool found = false;

		cin >> nBugs >> nInteractions;

		vector<vector<int>> adjList(nBugs);

		for (i = 0; i < nInteractions; i++)
		{
			cin >> bug1 >> bug2;
			adjList[bug1 - 1].push_back(bug2 - 1);
			adjList[bug2 - 1].push_back(bug1 - 1);
		}

		found = checkBugInteraction(adjList, nBugs);

		cout << "\nScenario #" << scenarios + 1 << endl;
		if (found)
			cout << "Suspicious bugs found!";
		else
			cout << "No suspicious bugs found!";
	}
}

bool checkBugInteraction(vector<vector<int>> adjList, int nBugs)
{
	int i, j, front, neighbourBugGroup;
	vector<int> bugGroup(nBugs), visited(nBugs);
	queue<int> bugQueue;

	for (i = 0; i < nBugs; i++)
	{
		bugGroup[i] = 0;
		visited[i] = false;
	}

	for (i = 0; i < nBugs; i++)
	{
		if (adjList[i].size() <= 0 || visited[i] == true)
			continue;
		bugGroup[i] = 1;
		visited[i] = true;
		bugQueue.push(i);

		while (bugQueue.size() > 0)
		{
			front = bugQueue.front();
			visited[front] = true;
			bugQueue.pop();

			for (j = 0; j < adjList[front].size(); j++)
			{
				neighbourBugGroup = bugGroup[adjList[front][j]];
				if (neighbourBugGroup != 0 && neighbourBugGroup == bugGroup[front])
					return true;
				if (neighbourBugGroup != 0)
					continue;
				if (neighbourBugGroup == 0 && bugGroup[front] == 1)
					bugGroup[adjList[front][j]] = 2;
				else
					bugGroup[adjList[front][j]] = 1;
				bugQueue.push(adjList[front][j]);
			}
		}
	}

	return false;
}
