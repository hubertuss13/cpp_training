#include <iostream>
#include <string>

// ─────────────────────────────────────────────────────────────────────────────
// KONFIGURACJA
// Siatka liter N×M w której szukamy słowa WORD.
// Każde pole siatki może być użyte maksymalnie raz (visited[][]).
// ─────────────────────────────────────────────────────────────────────────────
const int N = 5;  // wiersze
const int M = 5;  // kolumny

char grid[N][M] = {
    {'A', 'B', 'S', 'E', 'E'},
    {'F', 'C', 'N', 'S', 'N'},
    {'A', 'D', 'A', 'A', 'A'},
    {'R', 'G', 'K', 'K', 'T'},
    {'E', 'E', 'E', 'E', 'E'},
};

const std::string WORD = "SNAKE";

// Tablica odwiedzonych pól – każda litera może być użyta tylko raz.
// Wzorzec identyczny jak przy myszy i skoczku:
//   przed wejściem: visited[r][c] = true
//   po powrocie:    visited[r][c] = false
bool visited[N][M] = {};

// ─────────────────────────────────────────────────────────────────────────────
// 8 KIERUNKÓW RUCHU – góra, dół, lewo, prawo i 4 przekątne.
// Przy skoczku były to skoki L-kształtne – tutaj ruch o jedno pole.
// ─────────────────────────────────────────────────────────────────────────────
const int DR[] = {-1, -1, -1,  0,  0,  1,  1,  1};
const int DC[] = {-1,  0,  1, -1,  1, -1,  0,  1};

// ─────────────────────────────────────────────────────────────────────────────
// IS_VALID – sprawdza czy ruch na pole (row, col) jest legalny:
//   1. Pole mieści się w granicach siatki
//   2. Pole nie było jeszcze odwiedzone w tej ścieżce
//   3. Litera na polu zgadza się z aktualnie szukaną literą słowa
// ─────────────────────────────────────────────────────────────────────────────
bool isValid(int row, int col, char letter)
{
    if (row < 0 || row >= N || col < 0 || col >= M) return false;
    if (visited[row][col]) return false;
    if (grid[row][col] != letter) return false;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// SOLVE – backtracking szukający kolejnych liter słowa.
//
// Parametry:
//   row, col     – aktualna pozycja w siatce
//   letterIndex  – indeks litery w słowie którą aktualnie dopasowujemy
//
// Zwraca true  gdy wszystkie litery słowa zostały dopasowane.
// Zwraca false gdy z tej pozycji nie da się dopasować reszty słowa.
//
// Kluczowa różnica względem poprzednich zadań:
//   - warunek stopu to dopasowanie WSZYSTKICH liter słowa (letterIndex == WORD.size())
//   - na każdym kroku sprawdzamy czy litera na polu zgadza się z WORD[letterIndex]
// ─────────────────────────────────────────────────────────────────────────────
bool solve(int row, int col, int letterIndex)
{
    // WARUNEK STOPU: dopasowaliśmy wszystkie litery słowa – sukces!
    if (letterIndex == (int)WORD.size()) return true;

    // Próbujemy wszystkie 8 kierunków ruchu
    for (int d = 0; d < 8; d++)
    {
        int newRow = row + DR[d];
        int newCol = col + DC[d];

        // Sprawdzamy czy ruch jest legalny i czy litera pasuje
        if (!isValid(newRow, newCol, WORD[letterIndex])) continue;

        // ZRÓB KROK: oznacz pole jako odwiedzone
        visited[newRow][newCol] = true;

        // IDŹ GŁĘBIEJ: szukaj następnej litery słowa
        if (solve(newRow, newCol, letterIndex + 1)) return true;

        // COFNIJ KROK: ta ścieżka nie doprowadziła do rozwiązania
        visited[newRow][newCol] = false;
    }

    // Żaden kierunek nie doprowadził do dopasowania reszty słowa
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// PRINT_GRID – wypisuje siatkę
// ─────────────────────────────────────────────────────────────────────────────
void printGrid()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
            std::cout << grid[r][c] << " ";
        std::cout << "\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// Pętla startowa – przeszukuje wszystkie możliwe punkty startowe.
// Funkcja solve() zajmuje się jedną ścieżką od konkretnego punktu.
// main() odpowiada za próbowanie wszystkich możliwych startów.
// ─────────────────────────────────────────────────────────────────────────────
int main()
{
    std::cout << "===== Word Search =====\n\n";
    std::cout << "Siatka:\n";
    printGrid();
    std::cout << "\nSzukamy slowa: " << WORD << "\n\n";

    bool found = false;

    // Przeszukujemy każde pole siatki jako potencjalny punkt startowy.
    // Jeśli pole zawiera pierwszą literę słowa – próbujemy stąd.
    for (int r = 0; r < N && !found; r++)
    {
        for (int c = 0; c < M && !found; c++)
        {
            // Pierwsza litera musi pasować zanim w ogóle wywołamy solve()
            if (grid[r][c] != WORD[0]) continue;

            std::cout << "Probuje start z (" << r << "," << c << ")...\n";

            // Oznaczamy punkt startowy jako odwiedzony
            visited[r][c] = true;

            // solve() szuka od drugiej litery (letterIndex=1)
            // bo pierwsza litera już jest dopasowana w punkcie startowym
            if (solve(r, c, 1))
            {
                std::cout << "Znaleziono slowo \"" << WORD
                          << "\" startujac z (" << r << "," << c << ")!\n";

                // Wypisujemy siatkę z zaznaczoną ścieżką
                std::cout << "\nSiatka z zaznaczona sciezka (* = uzyta litera):\n";
                for (int gr = 0; gr < N; gr++)
                {
                    for (int gc = 0; gc < M; gc++)
                    {
                        if (visited[gr][gc])
                            std::cout << "* ";
                        else
                            std::cout << grid[gr][gc] << " ";
                    }
                    std::cout << "\n";
                }
                found = true;
            }
            else
            {
                // Reset visited dla następnej próby
                visited[r][c] = false;
            }
        }
    }

    if (!found)
        std::cout << "Slowo \"" << WORD << "\" nie zostalo znalezione w siatce.\n";

    return 0;
}
