#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

ifstream fin("sortaret.in");
ofstream gout("sortaret.out");

int N_VERTEX;
int M_EDGES;

int in_deg[50001] = {0};
// Not necessary, just for fun
int out_deg[50001] = {0};

vector<int> edges[50001];
vector<int> sorted;

void remove_vertex(int vertex)
{
    // Decrease incoming score of connected nodes
    for (int outgoing = 0; outgoing < edges[vertex].size(); ++outgoing)
    {
        --in_deg[edges[vertex][outgoing]];
    }
    // Empty vector of edges outgoing from vertex - not mandatory
    edges[vertex].clear();
    // Mark as visited
    in_deg[vertex] = -1;
}

void read_input()
{
    int x;
    int y;

    fin >> N_VERTEX;
    fin >> M_EDGES;

    for (int i = 0; i < M_EDGES; ++i)
    {
        // Read all edges in adjacency list
        fin >> x >> y;
        edges[x].push_back(y);
        // Count in degree of node
        ++in_deg[y];
        // Count out degree of node
        ++out_deg[x];
    }
}

void topological_sort()
{
    int count_removed = 0;

    while (count_removed < N_VERTEX)
    {
        for (int i = 1; i <= N_VERTEX; ++i)
        {
            if (in_deg[i] == 0)
            {
                sorted.push_back(i);
                remove_vertex(i);
                ++count_removed;
            }
        }
    }
}

void empty_graph()
{
    int current_node = -1;
    vector<int>::iterator it;
    // Add all zero-deg nodes to queue
    for (int i = 1; i <= N_VERTEX; ++i)
    {
        if (in_deg[i] == 0)
        {
            sorted.push_back(i);
        }
    }
    // Traverse zero-deg queue and remove edges to neighbouring nodes
    for (int i = 0; i < N_VERTEX; ++i)
    {
        current_node = sorted[i];

        for (it = edges[current_node].begin(); it != edges[current_node].end(); ++it)
        {
            --in_deg[*it];
            if (in_deg[*it] == 0)
            {
                sorted.push_back(*it);
            }
        }
    }
}

void write_output()
{
    for (int i = 0; i < sorted.size(); ++i)
    {
        gout << sorted[i] << " ";
    }
    gout << "\n";
}

int main()
{

    read_input();
    // topological_sort();
    empty_graph();
    write_output();

    fin.close();
    gout.close();

    return 0;
}