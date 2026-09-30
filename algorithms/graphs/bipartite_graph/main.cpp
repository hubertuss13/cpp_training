#include <iostream>
#include <vector>
#include <queue>

// Graf jest dwudzielny gdy możesz pokolorować jego węzły dwoma kolorami (np. 0 i 1)
// tak żeby żadne dwa sąsiadujące węzły nie miały tego samego koloru.

// Graf dwudzielny:        Graf NIEdwudzielny:
// 0 --- 1                 0 --- 1
// |     |                  \   /
// 2 --- 3                    2
// Kolorowanie:            Próba kolorowania:
// 0=czerwony              0=czerwony
// 1=niebieski             1=niebieski
// 2=niebieski             2=? (sąsiaduje z 0=czerwonym i 1=niebieskim)
// 3=czerwony ✅               musi być niebieski i czerwony jednocześnie ❌

// jeśli sąsiad jest już pokolorowany i ma ten sam kolor co bieżący węzeł → graf NIE jest dwudzielny

const int V = 4;
std::vector<std::vector<int>> neighbors(V);
std::vector<int> color(V, -1);  // -1 = niepokolorowany
                                //  0 = kolor pierwszy
                                //  1 = kolor drugi
std::queue<int> q;

void addEdge(int u, int v)
{
    neighbors[u].push_back(v);
    neighbors[v].push_back(u);
}

bool isGraphBipartite(int start)
{
    color[start] = 0;
    q.push(start);

    while (false == q.empty())
    {
        int currentNode = q.front();
        q.pop();
        
        for (auto n : neighbors[currentNode])
        {
            if (color[n] == -1)     // sasiad jeszcze niepokolorowany == nieodwiedzony → koloruj i wrzuć do kolejki
            {
                color[n] = 1 - color[currentNode];
                q.push(n);
            }
            else if (color[n] == color[currentNode])    // pokolorowany → sprawdz konflikt
            {
                return false;
            }
        }
    }

    return true;
}

void reset()
{
    for (int i = 0; i < V; i++)
    {
        neighbors[i].clear();
        color[i] = -1;
    }
    while (!q.empty())
        q.pop();
}


int main()
{
    std::cout << "===== Czy graf jest dwudzielny (BFS) =====" << std::endl;

    // TEST 1: kwadrat - dwudzielny
    std::cout << "Test 1: Kwadrat";
    std::cout << R"(
Graf 1:
0 --- 1
|     |
2 --- 3
    )";
    addEdge(0, 1);
    addEdge(1, 3);
    addEdge(0, 2);
    addEdge(2, 3);
    std::cout << (isGraphBipartite(0) ? "Dwudzielny ✓" : "NIEdwudzielny") << "\n\n";
    reset();

    // TEST 2: trojkat - NIEdwudzielny
    std::cout << "Test 2: Trojkat";
    std::cout << R"(
Graf 2:
0 --- 1
 \   /
   2
    )";
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(0, 2);
    std::cout << (isGraphBipartite(0) ? "Dwudzielny" : "NIEdwudzielny ✓") << "\n\n";

    return 0;
}
