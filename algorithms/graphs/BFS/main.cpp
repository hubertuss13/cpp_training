#include <iostream>
#include <vector>
#include <queue>

const int V = 6;                                // liczba wierzchołków w grafie 0d 0 do 5
std::vector<std::vector<int>> neighbours(V);    // lista sasiedztwa: neighbours[i]: lista sasiadow wierzchołka i
std::vector<bool> visited(V, false);            // czy dany wierzchołek był już odwiedzony, żeby nie wpaść w pętlę nieskończoną,
                                                // wracając do tych samych wierzchołków
std::queue<int> q;

void addEdge(int u, int v)
{
    // dodajemy krawędź w obie strony (graf nieskierowany)
    neighbours[u].push_back(v);
    neighbours[v].push_back(u);
}

void BFS(int node)
{
    // KROK 1: wrzucamy wierzchołek startowy do kolejki
    // i OD RAZU oznaczamy go jako odwiedzony
    // (ważne! -> nie czekamy z tym az go wyjmiemy z kolejki -
    // inaczej ten sam wierzchołek mógłby trafić do kolejki wielokrotnie)
    q.push(node);
    visited[node] = true;

    // KROK 2: główna pętla - działa dopóki jest cokolwiek do zbadania
    while (false == q.empty())
    {
        // KROK 3: bierzemy wierzchołek z przodu kolejki
        int currentNode = q.front();
        std::cout << "Odwiedzam V = " << currentNode << std::endl;
        q.pop();    // usuwamy go z kolejki -> został już obsłużony

        // KROK 4: przeglądamy WSZYSTKICH sąsiadów bieżącego wierzchołka
        for (auto n : neighbours[currentNode])
        {
            // KROK 5: jeśli sąsiad jeszcze nie odwiedzony => to go odwiedzamy
            if (false == visited[n])
            {
                visited[n] = true;    // od razu go oznaczamy jako odwiedzony (patrz komentarz KROK 1)
                q.push(n);                      // dorzucamy go na koniec kolejki do procesowania

                // NIE wywołujemy tu żadnej funkcji REKURENCYJNEJ.
                // po prostu dokładamy pracę "na później" do kolejki
                // To dlatego BFS nie potrzebuje backtrackingu.
                // Nie ma tu żadnego "zagłębiania się", więc nie ma skąd się cofać.
            }
        }
    }
}

int main()
{
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(4, 5);
    BFS(0);

    return 0;
}
