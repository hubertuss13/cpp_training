#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>    // std::reverse


// Graf:
// 0 --- 1 --- 3
// |           |
// 2 --------- 4

// Najkrótsza ścieżka 0→4:
// DFS mógłby znaleźć: 0→1→3→4  (długość 3)
// BFS zawsze znajdzie: 0→2→4    (długość 2) ✅

const int V = 5;
std::vector<std::vector<int>> neighbours(V);
std::vector<bool> visited(V, false);
std::vector<int> parent(V, -1);
std::vector<int> path;
std::queue<int> q;

void addEdge(int u, int v)
{
    neighbours[u].push_back(v);
    neighbours[v].push_back(u);
}

void printPath(int end)
{
    for (int node = end; node != -1; node = parent[node])
    {
        path.push_back(node);
    }
    std::reverse(path.begin(), path.end());
    std::cout << "\nNajkrotsza sciezka w grafie = [ ";
    for (auto x : path)
        std::cout << x << " ";
    std::cout << "]" << std::endl << std::endl;
}

void bfsFindShortestPath(int start, int end)
{
    visited[start] = true;
    q.push(start);

    while (false == q.empty())
    {
        int currentNode = q.front();
        q.pop();
        std::cout << "Odwiedzam wezel nr: " << currentNode << std::endl;
        if (currentNode == end)
        {
            printPath(end);
            break;
        }
        for (auto n : neighbours[currentNode])
        {
            if (false == visited[n])
            {
                parent[n] = currentNode;
                q.push(n);
                visited[n] = true;
            }
        }
    }
}

void printGraph() {
    std::cout << "Znajdowanie najkrotszej sciezki w grafie";
    std::cout << R"(
Graf:
0 --- 1 --- 3
|           |
2 --------- 4
)" << '\n';
}

int main()
{
    printGraph();
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(3, 4);
    bfsFindShortestPath(0, 4);

    return 0;
}
