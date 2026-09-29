#include <iostream>
#include <vector>

// Cykl - ścieżka która zaczyna i kończy się w tym samym węźle bez powtarzania krawędzi
// Graf BEZ cyklu (drzewo):    Graf Z cyklem:
//     0                           0
//    / \                         / \
//   1   2                       1   2
//  /                             \ /
// 3                               3
//
// === Idea wykrywania cyklu przez DFS ===
// Przy DFS masz 2 struktury:
// visited[]  – czy węzeł był kiedykolwiek odwiedzony
// parent[]   – skąd przyszliśmy do danego węzła
// Cykl wykrywasz gdy podczas DFS natrafisz na sąsiada który:
// --> jest już visited
// --> nie jest twoim rodzicem


// 0 --- 1 --- 2
// |           |
// └───────────┘

// DFS z 0: odwiedzamy 0→1→2
// Z węzła 2 patrzymy na sąsiadów: 1 (rodzic, skip), 0
// 0 jest visited I NIE jest rodzicem 2 → CYKL! ✅

const int V = 3;
std::vector<std::vector<int>> neighbors(V);
std::vector<bool> visited(V);

void addEdge(int u, int v)
{
    neighbors[u].push_back(v);
    neighbors[v].push_back(u);
}

bool dfsCycle(int currentNode, int parentNode)
{
    visited[currentNode] = true;
    std::cout << "Odwiedzam wezel nr: " << currentNode << std::endl;

    for (auto n : neighbors[currentNode])
    {
        if (n == parentNode) continue;
        if (visited[n] == false)
        {
            if (true == dfsCycle(n, currentNode)) return true;
        }
        else
        {
            // wykryto cykl
            return true;
        }
    }

    return false;
}

int main()
{
    std::cout << "===== Wykrywanie cykli w grafie (DFS) =====" << std::endl;
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(0, 2);

    if (true == dfsCycle(0, -1))
    {
        std::cout << "Znaleziono cykl w grafie!\n";
    }
    else
    {
        std::cout << "Nie znaleziono cyklu w grafie\n";
    }

    return 0;
}
