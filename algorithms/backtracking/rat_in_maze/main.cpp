#include <iostream>

// ─────────────────────────────────────────────────────────────────────────────
// KONFIGURACJA
// N×N siatka gdzie:
//   1 = pole po którym można chodzić
//   0 = ściana (blokada)
// Szczur startuje z (0,0) i szuka wszystkich ścieżek do (N-1, N-1).
// ─────────────────────────────────────────────────────────────────────────────
const int N = 4;

int maze[N][N] = {
    {1, 0, 0, 0},
    {1, 1, 0, 1},
    {0, 1, 0, 0},
    {1, 1, 1, 1},
};

// Tablica odwiedzonych pól – szczur nie może odwiedzić tego samego pola dwa razy.
// Wzorzec identyczny jak przy myszy i skoczku:
//   przed wejściem: visited[r][c] = true
//   po powrocie:    visited[r][c] = false
bool visited[N][N] = {};

int solutionCnt = 0;

// 4 kierunki ruchu: góra, lewo, prawo, dół
const int DR[] = {-1, 0,  0, 1};
const int DC[] = { 0, -1, 1, 0};

// ─────────────────────────────────────────────────────────────────────────────
// IS_VALID – sprawdza czy ruch na pole (row, col) jest legalny:
//   1. Pole mieści się w granicach siatki
//   2. Pole nie było jeszcze odwiedzone
//   3. Pole jest przejezdne (maze[row][col] == 1)
// ─────────────────────────────────────────────────────────────────────────────
bool isValid(int row, int col)
{
    if (row < 0 || row >= N || col < 0 || col >= N) return false;
    if (visited[row][col]) return false;
    if (maze[row][col] != 1) return false;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// PRINT_PATH – wypisuje siatkę z zaznaczoną ścieżką szczura.
// '*' = pole odwiedzone przez szczura w bieżącym rozwiązaniu.
// Uwaga: oznaczamy (N-1,N-1) osobno bo warunek stopu następuje
// PRZED oznaczeniem tego pola jako visited.
// ─────────────────────────────────────────────────────────────────────────────
void printPath()
{
    std::cout << "Rozwiazanie " << solutionCnt << ":\n";
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            // Pole odwiedzone LUB pole docelowe (zawsze część ścieżki)
            bool isGoal = (r == N-1 && c == N-1);
            if (visited[r][c] || isGoal)
                std::cout << "* ";
            else
                std::cout << maze[r][c] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// SOLVE – backtracking szukający wszystkich ścieżek od (row,col) do (N-1,N-1).
//
// Zwraca void bo szukamy WSZYSTKICH rozwiązań – nie przerywamy po pierwszym.
// (Przy Sudoku i myszy zwracaliśmy bool bo szukaliśmy JEDNEGO rozwiązania.)
//
// Kluczowy wzorzec:
//   oznacz pole → idź głębiej → cofnij oznaczenie
// ─────────────────────────────────────────────────────────────────────────────
void solve(int row, int col)
{
    // WARUNEK STOPU: szczur dotarł do celu – zapisujemy rozwiązanie
    if (row == N-1 && col == N-1)
    {
        solutionCnt++;
        printPath();
        return;  // wracamy żeby szukać kolejnych ścieżek
    }

    // Próbujemy wszystkie 4 kierunki ruchu
    for (int d = 0; d < 4; d++)
    {
        int newRow = row + DR[d];
        int newCol = col + DC[d];

        if (!isValid(newRow, newCol)) continue;  // ruch nielegalny – pomijamy

        // ZRÓB KROK: wejdź na nowe pole
        visited[newRow][newCol] = true;

        // IDŹ GŁĘBIEJ: szukaj ścieżki z nowej pozycji
        solve(newRow, newCol);

        // COFNIJ KROK: to pole może być użyte przez inną ścieżkę
        visited[newRow][newCol] = false;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main()
{
    std::cout << "===== Rat in a Maze =====\n\n";

    std::cout << "Labirynt:\n";
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
            std::cout << maze[r][c] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";

    // Startujemy z (0,0) – oznaczamy jako odwiedzone przed wywołaniem solve()
    visited[0][0] = true;
    solve(0, 0);

    if (solutionCnt == 0)
        std::cout << "Brak sciezki z (0,0) do (" << N-1 << "," << N-1 << ")!\n";
    else
        std::cout << "Liczba rozwiazań: " << solutionCnt << "\n";

    return 0;
}
