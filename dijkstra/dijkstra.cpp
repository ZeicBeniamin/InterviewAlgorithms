#include <iostream>
#include <fstream>
#include <utility>
#include <queue>
#include <functional>
#include <limits.h>

#define N_MAX 50000
#define M_MAX 250000
#define UNDEFINED INT_MAX - 1
#define CHEAT INT_MAX

using namespace std;

ifstream fin("dijkstra.in");
ofstream gout("dijkstra.out");

int distances[N_MAX + 1];

bool compare(std::pair<int, int> l, std::pair<int, int> r)
{
	return l.second > r.second;
}

bool visited[N_MAX + 1] = {0};
std::vector<pair<int, int>> adjacent[N_MAX + 1];
std::priority_queue<std::pair<int, int>,
					vector<std::pair<int, int>>,
					std::function<bool(std::pair<int, int>,
									   std::pair<int, int>)>>
	node_q(compare);

void read(int &num_nodes, int &num_edges)
{
	int n1;
	int n2;
	int weight;

	fin >> num_nodes >> num_edges;
	for (int i = 0; i < num_edges; ++i)
	{
		fin >> n1 >> n2 >> weight;

		adjacent[n1].push_back(make_pair(n2, weight));
	}
}

void find_path(int source, int num_nodes)
{
	for (int i = 0; i < N_MAX + 1; ++i)
	{
		distances[i] = UNDEFINED;
	}
	// Put initial node in queue, set distance to zero
	distances[source] = 0;
	node_q.push(std::make_pair(source, 0));

	int iter = 0;
	int z = 40;
	int last_weight = 0;

	while (!node_q.empty())
	{
		++iter;
		std::pair<int, int> currentNode = node_q.top();
		node_q.pop();

		if (iter > 15461 - z && iter < 15461 + z)
		{
			cout << "Node " << currentNode.first << "   \t\t" << distances[currentNode.first];
		}

		if (visited[currentNode.first])
		{
			if (iter > 15461 - z && iter < 15461 + z)
			{
				cout << "+++++" << "\n";
			}

			continue;
		}
		if (iter > 15461 - z && iter < 15461 + z)
		{
			cout << "\n";
		}
		if (last_weight > distances[currentNode.first]) {
			cout << "Storing! " << "Last w: " << last_weight << " curr: " << distances[currentNode.first] << "\n";
		}

		for (int i = 0; i < adjacent[currentNode.first].size(); ++i)
		{
			int nextNode = adjacent[currentNode.first][i].first;

			if (visited[nextNode])
			{
				continue;
			}

			int edgeWeight = adjacent[currentNode.first][i].second;

			int potential_next_distance = distances[currentNode.first] + edgeWeight;

			if (distances[nextNode] >= potential_next_distance)
			{
				distances[nextNode] = potential_next_distance;
			}

			node_q.push(std::make_pair(nextNode, distances[nextNode]));
		}

		visited[currentNode.first] = true;
		last_weight = distances[currentNode.first];
	}
}

void print(int num_nodes)
{
	for (int i = 2; i <= num_nodes; ++i)
	{
		if (distances[i] == UNDEFINED)
		{
			gout << 0 << " ";
		}
		else
		{
			gout << distances[i] << " ";
		}
	}
}

int main()
{
	int num_nodes;
	int num_edges;
	read(num_nodes, num_edges);
	// cout << "Num nodes " << num_nodes << "\n";
	find_path(1, num_nodes);
	print(num_nodes);
}