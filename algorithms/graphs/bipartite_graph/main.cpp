#include <iostream>
#include <vector>

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


void addEdge(int u, int v)
{
    neighbors[u].push_back(v);
    neighbors[v].push_back(u);
}


int main()
{
    std::cout << "===== Czy graf jest dwudzielny (BFS) =====" << std::endl;
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(0, 2);



    return 0;
}
