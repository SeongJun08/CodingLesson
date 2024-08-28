#include <iostream>
#include <vector>
// 2. 연결된 노드의 갯수, 그래프,  2024 08 26 
using namespace std;

void DFS(int node, vector<vector<int>>& adjList, vector<bool>& visited)
{
    visited[node] = true;

    for (const auto &neighbor : adjList[node])
    {
        if (!visited[neighbor])
        {
            DFS(neighbor, adjList, visited);
        }
    }
}

int CountComponents(int n, vector<vector<int>> &edges)
{
    // adjacency list
    vector<vector<int>> adjList(n);
    for (auto& edge : edges) //vector<int>
    {
        int u = edge[0];
        int v = edge[1];

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<bool> visited(n, false);
    int count{};
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            DFS(i, adjList, visited);
            count++;
        }
    }
    return count;
}

int main()
{
    vector<vector<int>> e1 = { {0,1}, {1,2}, {3,4} };

    std::cout << CountComponents(5, e1) << std::endl;

    vector<vector<int>> e2 = { {0,1}, {1,2}, {2,3}, { 3,4 } };

    std::cout << CountComponents(5, e2) << std::endl;


}
