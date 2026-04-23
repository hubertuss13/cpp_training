#include "genPermGlobalContext.h"

PermutationGlobalContext::PermutationGlobalContext(std::vector<int> collection) :
    Collection(std::move(collection)),
    N(static_cast<int>(Collection.size())),
    used(N, false),
    current(),
    resultCnt(0)
{
    // to, co NIE jest const — możemy zainicjować w ciele konstruktora np tak:
    // used = std::vector<bool>(N, false);
    // current = std::vector<int>();  // lub po prostu nic — domyślny konstruktor zrobi to za nas
    // resultCnt = 0;
}

// ============================================================
// Jedyny parametr jaki potrzebujemy to 'depth' –
// czyli jak głęboko jesteśmy w drzewie decyzji.
// Innymi słowy: ile elementów już wybraliśmy do 'current'.
// ============================================================
void PermutationGlobalContext::generatePerm(int depth)
{
    // ---------------------------------------------------------
    // WARUNEK STOPU: depth == N oznacza, że current 
    // zawiera wszystkie N elementów -> mamy gotową permutację!
    // ---------------------------------------------------------
    if (depth == N)
    {
        resultCnt++;
        std::cout << resultCnt << ": ";
        for (auto x : current) std::cout << x << " ";
        std::cout << std::endl;
        return;     // cofamy się o jeden poziom wyżej
    }

    // ---------------------------------------------------------
    // PĘTLA DECYZYJNA: na tym poziomie drzewa próbujemy
    // każdy element ze zbioru Collection jako następny kandydat.
    // ---------------------------------------------------------
    for (int i = 0; i < N; ++i)
    {
        // PRUNING: jeśli ten element jest już użyty – pomijamy.
        // To jest moment w którym odcinamy nielegalną gałąź
        // zamiast schodzić w nią i tracić czas.
        if (used[i] == true) continue;

        // ----- ZRÓB KROK -----
        // Wybieramy Collection[i] jako kolejny element permutacji.
        used[i] = true;
        current.push_back(Collection[i]);

        // ----- IDŹ GŁĘBIEJ -----
        // Schodzimy o poziom niżej – teraz wybieramy (depth+1) element.
        generatePerm(depth + 1);

        // ----- COFNIJ KROK -----
        // Wracamy do stanu SPRZED tej decyzji, żeby móc
        // wypróbować następny kandydat w pętli for.
        // Bez tych dwóch linii algorytm nie działa poprawnie.
        used[i] = false;
        current.pop_back();
    }
}

int PermutationGlobalContext::getResultCnt()
{
    return resultCnt;
}
