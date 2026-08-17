#include <iostream>
#include <vector>

// ─────────────────────────────────────────────────────────────────────────────
// REPREZENTACJA PLANSZY
// N×N plansza gdzie:
//   'M' – startowa pozycja myszy
//   'G' – ziarno (grain) które mysz musi zebrać
//   'H' – dziura (hole) do której mysz ucieka
//   'C' – kot (przeszkoda)
//   '.' – puste pole
// ─────────────────────────────────────────────────────────────────────────────
const int N = 5;

char board[N][N] = {
    {'M', '.', '.', 'C', '.'},
    {'.', 'C', '.', '.', '.'},
    {'.', '.', 'G', '.', '.'},
    {'.', '.', '.', 'C', '.'},
    {'.', '.', '.', '.', 'H'},
};

// Tablica odwiedzonych pól – zapobiega wchodzeniu na to samo pole dwa razy.
// Wzorzec identyczny jak used[] przy permutacjach:
//   przed wejściem: visited[r][c] = true
//   po powrocie:    visited[r][c] = false
bool visited[N][N] = {};

// Ścieżka którą przeszła mysz – zapisujemy kolejne pozycje
std::vector<std::pair<int,int>> path;

// Cztery kierunki ruchu: góra, dół, lewo, prawo
const int DR[] = {-1,  1, 0,  0};
const int DC[] = { 0,  0, -1, 1};

// ─────────────────────────────────────────────────────────────────────────────
// IS_VALID – sprawdza czy ruch na pole (row, col) jest legalny:
//   1. Pole mieści się w granicach planszy
//   2. Pole nie jest kotem
//   3. Pole nie było jeszcze odwiedzone
// ─────────────────────────────────────────────────────────────────────────────
bool isValid(int row, int col)
{
    if (row < 0 || row >= N || col < 0 || col >= N) return false;
    if (board[row][col] == 'C') return false;
    if (visited[row][col])      return false;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// FIND_HOLE – Etap 2: mysz zebrała ziarno i szuka dziury H.
// ─────────────────────────────────────────────────────────────────────────────
bool findHole(int row, int col)
{
    // WARUNEK STOPU: mysz stoi na dziurze – sukces!
    if (board[row][col] == 'H') return true;

    // Próbujemy każdy z 4 kierunków ruchu
    for (int d = 0; d < 4; d++)
    {
        int newRow = row + DR[d];
        int newCol = col + DC[d];

        if (!isValid(newRow, newCol)) continue;

        // ZRÓB KROK
        visited[newRow][newCol] = true;
        path.push_back({newRow, newCol});

        // IDŹ GŁĘBIEJ
        if (findHole(newRow, newCol)) return true;

        // COFNIJ KROK
        visited[newRow][newCol] = false;
        path.pop_back();
    }

    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// FIND_GRAIN – Etap 1: mysz szuka ziarna G.
// Gdy je znajdzie – uruchamia findHole() dla Etapu 2.
// ─────────────────────────────────────────────────────────────────────────────
bool findGrain(int row, int col)
{
    // WARUNEK STOPU: mysz stoi na ziarnie – Etap 1 zakończony!
    // Natychmiast startujemy Etap 2 z tej samej pozycji.
    if (board[row][col] == 'G')
    {
        // visited pozostaje bez zmian – mysz nie cofa się do odwiedzonych pól.
        // Etap 2 startuje z pozycji ziarna.
        return findHole(row, col);
    }

    // Próbujemy każdy z 4 kierunków ruchu
    for (int d = 0; d < 4; d++)
    {
        int newRow = row + DR[d];
        int newCol = col + DC[d];

        if (!isValid(newRow, newCol)) continue;

        // ZRÓB KROK
        visited[newRow][newCol] = true;
        path.push_back({newRow, newCol});

        // IDŹ GŁĘBIEJ
        if (findGrain(newRow, newCol)) return true;

        // COFNIJ KROK
        visited[newRow][newCol] = false;
        path.pop_back();
    }

    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// PRINT_PATH – wypisuje planszę z zaznaczoną trasą myszy
// ─────────────────────────────────────────────────────────────────────────────
void printPath()
{
    // Kopiujemy planszę żeby nie niszczyć oryginału
    char display[N][N];
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            display[r][c] = board[r][c];

    // Zaznaczamy ścieżkę na kopii planszy
    for (auto [r, c] : path)
        if (display[r][c] == '.') display[r][c] = '*';

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
            std::cout << display[r][c] << " ";
        std::cout << "\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main()
{
    std::cout << "===== Mysz, Ziarno i Kot =====\n\n";

    // Znajdź startową pozycję myszy
    int startRow = -1, startCol = -1;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (board[r][c] == 'M') { startRow = r; startCol = c; }

    std::cout << "Plansza poczatkowa:\n";
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++) std::cout << board[r][c] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";

    // Oznaczamy startową pozycję jako odwiedzoną i dodajemy do ścieżki
    visited[startRow][startCol] = true;
    path.push_back({startRow, startCol});

    if (findGrain(startRow, startCol))
    {
        std::cout << "Znaleziono sciezke!\n\n";
        std::cout << "Trasa myszy (" << path.size() << " krokow):\n";
        for (int i = 0; i < (int)path.size(); i++)
        {
            auto [r, c] = path[i];
            std::cout << "  krok " << i << ": (" << r << "," << c << ")";
            if (board[r][c] == 'M') std::cout << " [START]";
            if (board[r][c] == 'G') std::cout << " [ZIARNO]";
            if (board[r][c] == 'H') std::cout << " [DZIURA]";
            std::cout << "\n";
        }

        std::cout << "\nPlansza z trasa (* = odwiedzone):\n";
        printPath();
    }
    else
    {
        std::cout << "Brak sciezki – mysz nie moze uciec!\n";
    }

    return 0;
}
