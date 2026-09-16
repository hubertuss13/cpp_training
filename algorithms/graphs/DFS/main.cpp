#include <iostream>
#include <vector>

const int V = 6;                                // liczba wierzchołków w grafie 0d 0 do 5
std::vector<std::vector<int>> neighbours(V);    // lista sasiedztwa: neighbours[i]: lista sasiadow wierzchołka i
std::vector<bool> visited(V, false);            // czy dany wierzchołek był już odwiedzony, żeby nie wpaść w pętlę nieskończoną,
                                                // wracając do tych samych wierzchołków

void addEdge(int u, int v)
{
    // dodajemy krawędź w obie strony (graf nieskierowany)
    neighbours[u].push_back(v);
    neighbours[v].push_back(u);
}

// Depth-first search: algorytm przeszukiwania w głąb
// algorytm rekurencyjny => backtracking
void DFS(int node)
{
    // KROK 1: oznaczamy bieżący wierzchołek jako odwiedzony
    visited[node] = true;
    std::cout << "Wchodzę do wierzchołka V = " << node << std::endl;

    // KROK 2: Przeglądamy WSZYSTKICH sąsiadów bierzącego wierzchołka
    for (auto n : neighbours[node])
    {
        // KROK 3: Jeśli sąsiad jest jeszcze nie odwiedzony => idziemy w głąb (backtracking)
        if (false == visited[n])
        {
            // to jest wywołanie REKURENCYJNE
            // program "zawiesza" obecną funkcję DFS(node)
            // i przechodzi do wywołania DFS(n).
            // Stan bieżącej funkcji, czyli to w którym miejscu pętli 'for' jesteśmy,
            // jest zapamiętywany automatycznie na stosie wywołań (call stack)
            DFS(n);

            // <--- to miejsce to właśnie BACKTRACKING
            // program wraca właśnie tutaj, gdy wywołanie DFS(n) się zakończy
            // (czyli ta gałąź zostanie w pełni zbadana).
            // Pętla 'for' kontynuuje sprawdzanie KOLEJNYCH sąsiadów wierzchołka node
        }
    }
    // KROK 4: jeśli pętla for się skończyła -> znaczy, że sprawdziliśmy już wszystkich sąsiadów wierzchołka node.
    // Nie ma dokąd dalej iść z tego wierzchołka. Funkcja kończy działanie.
    // To automatycznie cofa nas do miejsca, skąd DFS(node) zostało wywołane.
    std::cout << "Cofam się z wierzchołka V = " << node << std::endl;
}

int main()
{
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(4, 5);
    DFS(0);

    return 0;
}
